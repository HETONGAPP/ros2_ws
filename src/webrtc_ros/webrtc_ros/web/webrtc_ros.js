window.WebrtcRos = (function() {
	var newStreamId = function() {
		return "webrtc_ros-stream-"+Math.floor(Math.random()*1000000000).toString();
	};
	
	var WebrtcRosConnection = function(signalingServerPath, configuration) {
		this.signalingServerPath = signalingServerPath || (window.location.protocol === 'https:' ? 'wss://' : 'ws://')+window.location.host+"/webrtc";
		this.onConfigurationNeeded = undefined;
		this.signalingChannel = null;
		this.peerConnection = null;
		this.receiveChannel = null;
		this.sendChannel = null;
		this.peerConnectionMediaConstraints = {
			optional: [{DtlsSrtpKeyAgreement: true}]
		};
		this.peerConnectionConfiguration = configuration;

		this.lastConfigureActionPromise = Promise.resolve([]);

		this.addStreamCallbacks = {};
		this.removeTrackCallbacks = {};
	};

	// WebrtcRosConnection.prototype.sendMessage = function() {
	// 	console.log("send the message =============================");
	// 	var message = "111111111111111111111111111";
	// 	sendChannel.send(message);

	// }
	WebrtcRosConnection.prototype.sendMessage = function(){
		console.log("send the message =============================");
		var message = "111111111111111111111111111";
		this.sendChannel.send(message);
	}
	WebrtcRosConnection.prototype.connect = function() {
		var self = this;
		this.close();
		this.signalingChannel = new WebSocket(this.signalingServerPath);
		this.signalingChannel.onmessage = function(e){ self.onSignalingMessage(e); };
		this.signalingChannel.onopen = function() {
			console.log("WebRTC signaling connection established");
			if (self.onConfigurationNeeded) {
				self.onConfigurationNeeded();
			}
		};
		this.signalingChannel.onerror = function() {
			console.error("WebRTC signaling error");
		};
		this.signalingChannel.onclose = function() {
			console.log("WebRTC signaling connection closed");
		};
		this.peerConnection = new RTCPeerConnection(this.peerConnectionConfiguration, this.peerConnectionMediaConstraints);
		this.peerConnection.onicecandidate = function(event) {
			if (event.candidate) {
				var candidate = {
					sdp_mline_index: event.candidate.sdpMLineIndex,
					sdp_mid: event.candidate.sdpMid,
					candidate: event.candidate.candidate,
					type: "ice_candidate"
				};
				self.signalingChannel.send(JSON.stringify(candidate));
			}
		};
		this.peerConnection.ontrack = function(event) {
			var callbackData = self.addStreamCallbacks[event.streams[0].id];
			if (callbackData) {
				event.streams[0].onremovetrack = function(event)
				{
					var callbackData = self.removeTrackCallbacks[event.track.id];
					if (callbackData)
					{
						callbackData.resolve({
							"track": event.track
						});
					}
				};
				callbackData.resolve({
					"stream": event.streams[0],
					"remove": new Promise(function(resolve, reject) {
						self.removeTrackCallbacks[event.track.id] = {
							"resolve": resolve,
							"reject": reject
						};
					})
				});
			}
		};

		this.sendChannel = this.peerConnection.createDataChannel("sendChannel");
    	this.sendChannel.onopen = function(event) {
        	console.log("*** send open ***");
			self.sendChannel.send("ssssssssssssssssssssssssssssssssssss");
    	};
    	this.sendChannel.onclose = function(event) {
        	console.log("*** send closed ***");
    	};
    	this.sendChannel.onerror = function(event) {console.log(err);};

		this.peerConnection.ondatachannel = function(event) {
			receiveChannel = event.channel;
			receiveChannel.onmessage = function(event) {
				console.log("*** receive: ",event.data);
			};
			receiveChannel.onopen = function(event) {
				console.log("*** receive:", receiveChannel.readyState);
			};
			receiveChannel.onclose = function(event) {
				console.log("*** receive:", receiveChannel.readyState);
			}
			receiveChannel.onerror = function(err){console.log(err);};
		};
	};
	WebrtcRosConnection.prototype.close = function() {
		if (this.peerConnection) {
			this.peerConnection.close();
			this.peerConnection = null;
		}
		if (this.signalingChannel) {
			this.signalingChannel.close();
			this.signalingChannel = null;
		}
		if (this.sendChannel) {
			this.sendChannel.onopen = null;
			this.sendChannel.onclose = null;
			this.sendChannel.close();
			this.sendChannel = null;
		}
		if (this.receiveChannel) {
			this.receiveChannel.onmessage = null;
			this.receiveChannel.onopen = null;
			this.receiveChannel.onclose = null;
			this.receiveChannel.close();
			this.receiveChannel = null;
		}
	};
	WebrtcRosConnection.prototype.onSignalingMessage = function(e) {
		var self = this;
		var dataJson = JSON.parse(e.data);
		if (dataJson.type === "offer") {
			console.log("Received WebRTC offer via WebRTC signaling channel");
			this.peerConnection.setRemoteDescription(new RTCSessionDescription(dataJson),
				function() {
					self.sendAnswer();
				},
				function(event) {
					console.error("onRemoteSdpError", event);
				}
			);
		}
		else if(dataJson.type === "ice_candidate") {
			console.log("Received WebRTC ice_candidate via WebRTC signaling channel");
			var candidate = new RTCIceCandidate({sdpMLineIndex: dataJson.sdp_mline_index, candidate: dataJson.candidate});
			this.peerConnection.addIceCandidate(candidate);
		}
		else
		{
			console.warn("Received unknown message type '" + dataJson.type + "' via WebRTC signaling channel");
		}
	};

	WebrtcRosConnection.prototype.sendAnswer = function() {
		var self = this;
		var mediaConstraints = {"optional": [
			{"OfferToReceiveVideo": true}
		]};
		this.peerConnection.createAnswer(
			function(sessionDescription) {
				self.peerConnection.setLocalDescription(sessionDescription);
				var data = JSON.stringify(sessionDescription);
				self.signalingChannel.send(data);
			}, function(error) {
				console.warn("Create answer error:", error);
			}, mediaConstraints
		);
	};
	WebrtcRosConnection.prototype.addRemoteStream = function(config) {
		var stream_id = newStreamId();
		var self = this;

		this.lastConfigureActionPromise = this.lastConfigureActionPromise.then(
			function(actions) {
				actions.push({"type":"add_stream", "id": stream_id});
				if(config.video) {
					actions.push({
						"type":"add_video_track",
						"stream_id": stream_id,
						"id": stream_id + "/" + config.video.id,
						"src": config.video.src
					});
				}
				if(config.audio) {
					actions.push({
						"type":"add_audio_track",
						"stream_id": stream_id,
						"id": stream_id + "/" + config.audio.id,
						"src": config.audio.src
					});
				}
				return actions;
			}
		);
		return new Promise(function(resolve, reject) {
			self.addStreamCallbacks[stream_id] = {
				"resolve": resolve,
				"reject": reject
			};
		});
	};
	WebrtcRosConnection.prototype.removeRemoteStream = function(stream) {
		var self = this;
		this.lastConfigureActionPromise = this.lastConfigureActionPromise.then(
			function(actions) {
				actions.push({"type":"remove_stream", "id": stream.id});
				return actions;
			}
		);
	};
	WebrtcRosConnection.prototype.addLocalStream = function(user_media_config, local_stream_config) {
		var self = this;
		return new Promise(function(resolve, reject) {
			self.lastConfigureActionPromise = self.lastConfigureActionPromise.then(
				function(actions) {
					return navigator.mediaDevices.getUserMedia(user_media_config).then(
						function(stream){
							actions.push({"type":"expect_stream", "id": stream.id});
							if(local_stream_config.video) {
								actions.push({
									"type":"expect_video_track",
									"stream_id": stream.id,
									"id": stream.getVideoTracks()[0].id,
									"dest":local_stream_config.video.dest
								});
							}
							self.peerConnection.addStream(stream);
							resolve({
								"stream": stream,
								"remove": new Promise(function(resolve, reject) {
									self.removeStreamCallbacks[stream.id] = {
										"resolve": resolve,
										"reject": reject
									};
								})
							});
							return actions;
						}
					);
				}
			);

		});
	};
	WebrtcRosConnection.prototype.removeLocalStream = function(stream) {
		var self = this;
		this.lastConfigureActionPromise = this.lastConfigureActionPromise.then(
			function(actions) {
				console.log("Removing stream");
				self.peerConnection.removeStream(stream);
				var callbackData = self.removeStreamCallbacks[stream.id];
				if (callbackData) {
					callbackData.resolve({
						"stream": stream
					});
				}
				return actions;
			}
		);
	};
	WebrtcRosConnection.prototype.sendConfigure = function() {
		var self = this;
		var currentLastConfigureActionPromise = this.lastConfigureActionPromise;
		this.lastConfigureActionPromise = Promise.resolve([]);

		currentLastConfigureActionPromise.then(
			function(actions) {
				var configMessage = {"type": "configure", "actions": actions};
				self.signalingChannel.send(JSON.stringify(configMessage));
				console.log("WebRTC ROS Configure: ", actions);
			}
		);
	};

	var WebrtcRos = {
		createConnection: function(signalingServerPath, configuration) {
			return new WebrtcRosConnection(signalingServerPath, configuration);
		}
	};
	function sendMessage()
	{
		console.log("sened222222222222222");
	}
	return WebrtcRos;
})();


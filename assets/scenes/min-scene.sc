{
  "name": "MyScene",
  "objects": [
    {
      "name": "MainPlayer",
      "type": "Player",
      "position": {
        "x": 0,
        "y": 2,
        "z": -7
      },
      "components": [
        {
          "type": "CameraComponent"
        },
        {
          "type": "PlayerControllerComponent"
        },
        {
          "type": "AudioListenerComponent"
        },
        {
          "type": "AudioComponent",
          "audio": [
            {
              "name": "shoot",
              "path": "audio/shoot.wav"
            },
            {
              "name": "step",
              "path": "audio/step.wav"
            },
            {
              "name": "jump",
              "path": "audio/jump.wav"
            }
          ]
        }
      ],
      "children": [
        {
          "name": "Gun",
          "type": "gltf",
          "path": "models/sten_gunmachine_carbine/scene.gltf",
          "position": {
            "x": 0.75,
            "y": -0.5,
            "z": -0.75
          },
          "scale": {
            "x": -1.0,
            "y": 1.0,
            "z": 1.0
          }
        }
      ]
    },
    {
         "name":"LeftWall",
         "position":{
            "x":-15.5,
            "y":3,
            "z":0
         },
         "components":[
            {
               "type":"MeshComponent",
               "mesh":{
                  "type":"box",
                  "x":1,
                  "y":5,
                  "z":30
               },
               "material":{
                  "path":"materials/checker.mat",
                  "params":{
                     "float3":[
                        {
                           "name":"color",
                           "value0":1.0,
                           "value1":1.0,
                           "value2":1.0
                        }
                     ]
                  }
               }
            },
            {
               "type":"PhysicsComponent",
               "collider":{
                  "type":"box",
                  "x":1,
                  "y":5,
                  "z":30
               },
               "body":{
                  "mass":0,
                  "friction":0.5,
                  "type":"static"
               }
            }
         ]
    },
    {
      "name": "Ground",
      "position": {
        "x": 0,
        "y": 0,
        "z": 0
      },
      "components": [
        {
          "type": "MeshComponent",
          "mesh": {
            "type": "box",
            "x": 30,
            "y": 1,
            "z": 30
          },
          "material": {
            "path": "materials/checker.mat"
          }
        },
        {
          "type": "PhysicsComponent",
          "collider": {
            "type": "box",
            "x": 30,
            "y": 1,
            "z": 30
          },
          "body": {
            "mass": 0,
            "friction": 0.5,
            "type": "static"
          }
        }
      ]
    },
    {
      "name": "Light",
      "position": {
        "x": -2,
        "y": 5,
        "z": 2
      },
      "components": [
        {
          "type": "LightComponent",
          "color": {
            "r": 1,
            "g": 1,
            "b": 1
          }
        }
      ]
    }
  ],
  "camera": "MainPlayer"
}
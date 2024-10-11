local Helper_Functions = require("HelperFunctions")

local CutScene = {}

local NameGrover = "Grover"
local NameWizard = "Wizard"

local CutScenes = {
    [1] = { -- intro cut scene
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local transformComponent = GameData:getTransformComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            if "run16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("run16", systemTime)
            end
            local endPos = vec2.new(250,450)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 20*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)

            dialogueText.name = NameGrover
            dialogueText.paragraph = "La La La LA LAAAA..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")
                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            
            if "idle16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle16", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "\n\n\t\t\tAAAHH! its a Wizard!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            transformComponent = GameData:getTransformComponent(WizardEntity)
            local endPos = vec2.new(320,427)
            positionX = transformComponent.position.x
            positionY = transformComponent.position.y
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 30*dt)
            positionY = Helper_Functions.MoveTowards(positionY, endPos.y, 30*dt)
            transformComponent.position = vec2.new(positionX, positionY)
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Im a Wizard going on a walk\n\nNmmm Nmm Nmm nn NMMM..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                transformComponent.position = endPos
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "What, whose that interupting my\n\nwalk!! Who ever interups my walks\n\ndeserves to be punished, from me\n\nthis forests evil Wizard!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "OHH it really is a Wizard!\n\nreally really really!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "HAY Wizard!!!\n\n\t\tI have a wish a REALLY big wish!\n\nI wan't you to make me tall,\n\nreally really REALLY TALL"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Oh you want to be tall\n\nI'll make you tall!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.trauma = 0.4
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "\t\t\t\t\t\t\t\tHA!!\n\n\t\t\t\t\t\t\tTake this!\n\n\t\t\t\tZAAAAAAAAAAAAAAH!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")
                GameData:playSound("../ExampleGame/Sounds/grow.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle32" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle32", systemTime)
            end
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Ha Im becomming taller!\n\n\t\tHa Yes!\n\nEven taller!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")
                GameData:playSound("../ExampleGame/Sounds/grow.wav")

                --cameraComponent.cameraPriority = 2
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle64" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle64", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "\n\n\n\t\t\t\t\t\t\tYes PERFECT!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")
                GameData:playSound("../ExampleGame/Sounds/transform.wav")

                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "transform" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("transform", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Wait whats happenting!!\n\nAAAHHHHHH!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent:addTrauma(0.7)
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle8" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle8", systemTime)
            end
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "What have you done I'm tiny now!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Ha Ha Ha!,\n\nwant me to turn you back you'll\n\nhave to catch me first"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 1
            local transformComponent = GameData:getTransformComponent(playerEntity)
            transformComponent.position = vec2.new(250,446)
            transformComponent = GameData:getTransformComponent(WizardEntity)
            local endPos = vec2.new(1000,427)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 60*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)
            
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Salutations"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
    },
    [2] = { -- First Time Catching the Wizard
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local transformComponent = GameData:getTransformComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            if "run16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("run16", systemTime)
            end
            local endPos = vec2.new(950,transformComponent.position.y)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 20*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)

            dialogueText.name = NameGrover
            dialogueText.paragraph = "Hey I caught you!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            
            if "idle16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle16", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "What kind of monster have you\n\nturned me into??\n\n\nTurn me BACK!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "HAHAHAHAHA\n\n\nYou really think you caught me??"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "I'm only here to have a little fun\n\nseeing you you get used to your\n\nnew body\n\n\nHAHAHA"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 1
            local transformComponent = GameData:getTransformComponent(WizardEntity)
            local endPos = vec2.new(1200,100)
            positionX = transformComponent.position.x
            positionY = transformComponent.position.y
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 60*dt)
            positionY = Helper_Functions.MoveTowards(positionY, endPos.y, 60*dt)
            transformComponent.position = vec2.new(positionX, positionY)
            
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Im heady off now\n\nHave fun getting this cliff."
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = vec2.new(1844,447)
            end
        end,
    },
    [3] = { -- Second Time Catching the Wizard
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "I see you're getting good at\n\nusing your new body"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 1
            local transformComponent = GameData:getTransformComponent(WizardEntity)
            local endPos = vec2.new(1844,100)
            positionX = transformComponent.position.x
            positionY = transformComponent.position.y
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 60*dt)
            positionY = Helper_Functions.MoveTowards(positionY, endPos.y, 60*dt)
            transformComponent.position = vec2.new(positionX, positionY)
            
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Now the real challenge begins\n\n\nMWHAHAHAHA"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = vec2.new(2660,447)
            end
        end,
    },
    [4] = { -- Second Time Catching the Wizard
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local transformComponent = GameData:getTransformComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            if "run16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("run16", systemTime)
            end
            local endPos = vec2.new(2560,transformComponent.position.y)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 20*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)

            dialogueText.name = NameGrover
            dialogueText.paragraph = "If I don't catch Mr Wizard I'll live\n\nlike this FOREVER"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            
            if "idle16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle16", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "FOREVERRRR!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Haha imagine if he stays like this\n\nforever..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 1
            local transformComponent = GameData:getTransformComponent(WizardEntity)
            local endPos = vec2.new(3666,120)
            positionX = transformComponent.position.x
            positionY = transformComponent.position.y
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 60*dt)
            positionY = Helper_Functions.MoveTowards(positionY, endPos.y, 60*dt)
            transformComponent.position = vec2.new(positionX, positionY)
            
            dialogueText.name = NameWizard
            dialogueText.paragraph = ""
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
    },
    [5] = { -- Second Time Catching the Wizard
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local transformComponent = GameData:getTransformComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            if "run16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("run16", systemTime)
            end
            local endPos = vec2.new(3636,transformComponent.position.y)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 20*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)

            dialogueText.name = NameGrover
            dialogueText.paragraph = "I got you cornered wizard!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity) 
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            
            if "idle16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle16", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Now unspell me"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "AHH NOOOOO"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "NOOOOOO LET GO OF ME"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Yes I can"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "No you can't"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Yes I can"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Ok fineeeee"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(WizardEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizard
            dialogueText.paragraph = "Here you go"
            cameraComponent.trauma = 0.3

            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 1
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Yay!\n\n\nBack to normal finally"
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, WizardEntity)
            local transformComponent = GameData:getTransformComponent(WizardEntity)
            local endPos = vec2.new(2560,100)
            positionX = transformComponent.position.x
            positionY = transformComponent.position.y
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 60*dt)
            positionY = Helper_Functions.MoveTowards(positionY, endPos.y, 60*dt)
            transformComponent.position = vec2.new(positionX, positionY)
            
            dialogueText.name = NameWizard
            dialogueText.paragraph = "SIGH\n\nMy developer doesn't know how to\n\nhave any fun..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                GameData:playSound("../ExampleGame/Sounds/scroll.wav")

                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = vec2.new(2560,447)
                GameData.gameState = eGameState.MainMenu
                local entities = GameData:getEntitiesWithIdentifier("CutScene")
                for _, entity in ipairs(entities) do
                    local luaComponent = GameData:getLuaComponent(entity)
                    local luaTable = luaComponent.table
                    luaTable.cutSceneHandled = nil
                    GameData.cutSceneIndex = 1
                    self.curStep = nil
                end
            end
        end,
    },
}

function CutScene:update(dt, systemTime)
    local dialogueText = GameData.dialogueText
    if not self.curStep then
        self.curStep = 1
        dialogueText.startTime = systemTime
    end

    local playerEntities = GameData:getEntitiesWithIdentifier("Player")
    local playerEntity
    for _, entity in ipairs(playerEntities) do
        playerEntity = entity
    end
    local WizardEntities = GameData:getEntitiesWithIdentifier("Wizzard")
    local WizardEntity
    for _, entity in ipairs(WizardEntities) do
        WizardEntity = entity
    end

    CutScenes[GameData.cutSceneIndex][self.curStep](self, dt, systemTime, dialogueText, playerEntity, WizardEntity)

    if #CutScenes[GameData.cutSceneIndex] < self.curStep then
        self.curStep = nil
        GameData.gameState = eGameState.Game
    end
end

return CutScene
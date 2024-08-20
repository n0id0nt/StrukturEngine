local Helper_Functions = require("HelperFunctions")

local CutScene = {}

local NameGrover = "Grover"
local NameWizzard = "Wizzard"

local CutScenes = {
    [1] = { -- intro cut scene
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity) 
            local transformComponent = GameData:getTransformComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            if "run16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("run16", systemTime)
            end
            local endPos = vec2.new(250,transformComponent.position.y)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 20*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)

            dialogueText.name = NameGrover
            dialogueText.paragraph = "La La La LA LAAAA..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity) 
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            
            if "idle16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle16", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "\n\n\t\t\tAAAHH! its a wizzard!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            transformComponent = GameData:getTransformComponent(wizzardEntity)
            local endPos = vec2.new(320,427)
            positionX = transformComponent.position.x
            positionY = transformComponent.position.y
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 30*dt)
            positionY = Helper_Functions.MoveTowards(positionY, endPos.y, 30*dt)
            transformComponent.position = vec2.new(positionX, positionY)
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Im a wizzard going on a walk\n\nNmmm Nmm Nmm nn NMMM..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                transformComponent.position = endPos
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "What, whose that interupting my\n\nwalk!! Who ever interups my walks\n\ndeserves to be punished, from me\n\nthis forests evil wizzard!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "OHH it really is a wizzard!\n\nreally really really!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "HAY WIZZARD!!!\n\n\t\tI have a wish a REALLY big wish!\n\nI wan't you to make me tall,\n\nreally really REALLY TALL"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Oh you want to be tall\n\nI'll make you tall!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.trauma = 0.4
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "\t\t\t\t\t\t\t\tHA!!\n\n\t\t\t\t\t\t\tTake this!\n\n\t\t\t\tZAAAAAAAAAAAAAAH!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle32" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle32", systemTime)
            end
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Ha Im becomming Taller!\n\n\t\tHa Yes!\n\nEven Taller!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 2
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle64" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle64", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "\n\n\n\t\t\t\t\t\t\tYes Perfect!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "transform" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("transform", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Wait Whats Happenting!!\n\nAAAHHHHHH!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent:addTrauma(0.7)
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle8" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle8", systemTime)
            end
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "What have you done I'm Tiny now!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Ha Ha Ha!,\n\nwant me to turn you back you'll\n\nhave to catch me first"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 1
            local transformComponent = GameData:getTransformComponent(playerEntity)
            transformComponent.position = vec2.new(250,446)
            transformComponent = GameData:getTransformComponent(wizzardEntity)
            local endPos = vec2.new(970,427)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 60*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)
            
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Salutations"
            if GameData.input:isInputJustReleased("NextDialogue") then
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
    },
    [2] = { -- intro cut scene
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity) 
            local transformComponent = GameData:getTransformComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            if "run16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("run16", systemTime)
            end
            local endPos = vec2.new(250,transformComponent.position.y)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 20*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)

            dialogueText.name = NameGrover
            dialogueText.paragraph = "La La La LA LAAAA..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity) 
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            
            if "idle16" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle16", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "\n\n\t\t\tAAAHH! its a wizzard!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            transformComponent = GameData:getTransformComponent(wizzardEntity)
            local endPos = vec2.new(320,427)
            positionX = transformComponent.position.x
            positionY = transformComponent.position.y
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 30*dt)
            positionY = Helper_Functions.MoveTowards(positionY, endPos.y, 30*dt)
            transformComponent.position = vec2.new(positionX, positionY)
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Im a wizzard going on a walk\n\nNmmm Nmm Nmm nn NMMM..."
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                transformComponent.position = endPos
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "What, whose that interupting my\n\nwalk!! Who ever interups my walks\n\ndeserves to be punished, from me\n\nthis forests evil wizzard!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "OHH it really is a wizzard!\n\nreally really really!!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "HAY WIZZARD!!!\n\n\t\tI have a wish a REALLY big wish!\n\nI wan't you to make me tall,\n\nreally really REALLY TALL"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Oh you want to be tall\n\nI'll make you tall!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.trauma = 0.4
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "\t\t\t\t\t\t\t\tHA!!\n\n\t\t\t\t\t\t\tTake this!\n\n\t\t\t\tZAAAAAAAAAAAAAAH!!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle32" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle32", systemTime)
            end
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Ha Im becomming Taller!\n\n\t\tHa Yes!\n\nEven Taller!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                --cameraComponent.cameraPriority = 2
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle64" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle64", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "\n\n\n\t\t\t\t\t\t\tYes Perfect!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "transform" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("transform", systemTime)
            end
            dialogueText.name = NameGrover
            dialogueText.paragraph = "Wait Whats Happenting!!\n\nAAAHHHHHH!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent:addTrauma(0.7)
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local spriteAnimationComponent = GameData:getSpriteAnimationComponent(playerEntity)
            if "idle8" ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation("idle8", systemTime)
            end
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            --cameraComponent.cameraPriority = 2
            dialogueText.name = NameGrover
            dialogueText.paragraph = "What have you done I'm Tiny now!"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(wizzardEntity)
            cameraComponent.cameraPriority = 2
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Ha Ha Ha!,\n\nwant me to turn you back you'll\n\nhave to catch me first"
            if GameData.input:isInputJustReleased("NextDialogue") then
                cameraComponent.cameraPriority = 0
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
            end
        end,
        function(self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)
            local cameraComponent = GameData:getCameraComponent(playerEntity)
            cameraComponent.cameraPriority = 1
            local transformComponent = GameData:getTransformComponent(playerEntity)
            transformComponent.position = vec2.new(250,446)
            transformComponent = GameData:getTransformComponent(wizzardEntity)
            local endPos = vec2.new(970,427)
            positionX = transformComponent.position.x
            positionX = Helper_Functions.MoveTowards(positionX, endPos.x, 60*dt)
            transformComponent.position = vec2.new(positionX, transformComponent.position.y)
            
            dialogueText.name = NameWizzard
            dialogueText.paragraph = "Salutations"
            if GameData.input:isInputJustReleased("NextDialogue") then
                self.curStep = self.curStep + 1
                dialogueText.startTime = systemTime
                transformComponent.position = endPos
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
    local wizzardEntities = GameData:getEntitiesWithIdentifier("Wizzard")
    local wizzardEntity
    for _, entity in ipairs(wizzardEntities) do
        wizzardEntity = entity
    end

    CutScenes[GameData.cutSceneIndex][self.curStep](self, dt, systemTime, dialogueText, playerEntity, wizzardEntity)

    if #CutScenes[GameData.cutSceneIndex] < self.curStep then
        self.curStep = nil
        GameData.gameState = eGameState.Game
    end
end

return CutScene
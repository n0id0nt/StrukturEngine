local Movement = require("Movement")

local PlayerScript = scriptTemplate.new()

local sizes = {
    "small8",
    "medium16",
    "large32",
    "giant64",
}
-- should put these on the players table
local playerAnimations = {
    small8 = {
        idle = "idle8",
        run = "run8",
    },
    medium16 = {
        idle = "idle16",
        run = "run16",
    },
    large32 = {
        idle = "idle32",
        run = "run32",
    },
    giant64 = {
        idle = "idle64",
        run = "run64",
    },
    transform = "transform",
}
local speedMultipliers = {
    small8 = 0.75,
    medium16 = 1,
    large32 = 1.5,
    giant64 = 1.25,
}
local collisionRecs = {
    small8 = rectangle.new(-2,32-8,4,8),
    medium16 = rectangle.new(-3,32-15,6,15),
    large32 = rectangle.new(-6,32-30,12,30),
    giant64 = rectangle.new(-11,32-59,22,59),
}
local groundedRecs = {
    small8 = rectangle.new(-2,32,4,0.25),
    medium16 = rectangle.new(-3,32,6,0.25),
    large32 = rectangle.new(-6,32,12,0.25),
    giant64 = rectangle.new(-11,32,22,0.25),
}

function math.clamp(val, lower, upper)
    if lower > upper then lower, upper = upper, lower end -- swap if boundaries supplied the wrong way
    return math.max(lower, math.min(upper, val))
end

function math.sign(number)
    return (number > 0 and 1) or (number < 0 and -1) or 0
end

function math.round(x)
    return x>=0 and math.floor(x+0.5) or math.ceil(x-0.5)
end

local function tileMapCollision(collisionRect, position)
    local tileMaps = GameData:getTileMapComponentsTable()
    for entity, component in pairs(tileMaps) do 
        local p1 = vec2.new(collisionRect.x + position.x, collisionRect.y + position.y)
        local p2 = vec2.new(collisionRect.x + position.x, collisionRect.y + position.y + collisionRect.height)
        local p3 = vec2.new(collisionRect.x + position.x + collisionRect.width, collisionRect.y + position.y)
        local p4 = vec2.new(collisionRect.x + position.x + collisionRect.width, collisionRect.y + position.y + collisionRect.height)
        
        if component:isPositionOnTile(p1) or component:isPositionOnTile(p2) or component:isPositionOnTile(p3) or component:isPositionOnTile(p4) then
            return true
        end
        -- need extra checks when rect is wider than the collision body
        if collisionRect.width > component.tileSize or collisionRect.height > component.tileSize then
            local p5 = vec2.new(collisionRect.x + position.x, collisionRect.y + position.y + collisionRect.height / 2)
            local p6 = vec2.new(collisionRect.x + position.x + collisionRect.width / 2, collisionRect.y + position.y)
            local p7 = vec2.new(collisionRect.x + position.x + collisionRect.width, collisionRect.y + position.y + collisionRect.height / 2)
            local p8 = vec2.new(collisionRect.x + position.x + collisionRect.width / 2, collisionRect.y + position.y + collisionRect.height)
            if component:isPositionOnTile(p5) or component:isPositionOnTile(p6) or component:isPositionOnTile(p7) or component:isPositionOnTile(p8) then
                return true
            end
        end
    end
    return false
end

local function tileMapCollisionLeft(collisionRect, position)
    local tileMaps = GameData:getTileMapComponentsTable()
    for entity, component in pairs(tileMaps) do 
        local p1 = vec2.new(collisionRect.x + position.x, collisionRect.y + position.y + collisionRect.height / 4)
        local p2 = vec2.new(collisionRect.x + position.x, collisionRect.y + position.y + collisionRect.height * 3 / 4)
        local p3 = vec2.new(collisionRect.x + position.x, collisionRect.y + position.y + collisionRect.height / 2)
        
        if component:isPositionOnTile(p1) or component:isPositionOnTile(p2) or component:isPositionOnTile(p3) then
            return true
        end
    end
    return false
end

local function tileMapCollisionRight(collisionRect, position)
    local tileMaps = GameData:getTileMapComponentsTable()
    for entity, component in pairs(tileMaps) do 
        local p1 = vec2.new(collisionRect.x + position.x + collisionRect.width, collisionRect.y + position.y + collisionRect.height / 4)
        local p2 = vec2.new(collisionRect.x + position.x + collisionRect.width, collisionRect.y + position.y + collisionRect.height * 3 / 4)
        local p3 = vec2.new(collisionRect.x + position.x + collisionRect.width, collisionRect.y + position.y + collisionRect.height / 2)
        
        if component:isPositionOnTile(p1) or component:isPositionOnTile(p2) or component:isPositionOnTile(p3) then
            return true
        end
    end
    return false
end

-- this is a skinnier check because the head is the skinniest part of the body and to eliminate the most false positives
local function tileMapCollisionUp(collisionRect, position)
    local tileMaps = GameData:getTileMapComponentsTable()
    for entity, component in pairs(tileMaps) do 
        local p1 = vec2.new(collisionRect.x + position.x + collisionRect.width  * 2 / 5, collisionRect.y + position.y)
        local p2 = vec2.new(collisionRect.x + position.x + collisionRect.width * 3 / 5, collisionRect.y + position.y)
        local p3 = vec2.new(collisionRect.x + position.x + collisionRect.width / 2, collisionRect.y + position.y)
        
        if component:isPositionOnTile(p1) or component:isPositionOnTile(p2) or component:isPositionOnTile(p3) then
            return true
        end
    end
    return false
end

PlayerScript.create = function(entity, dt, systemTime)
    print("Create Player")
    local cameraComponent = GameData:createCameraComponent(entity)
    cameraComponent.cameraPriority = 1
    cameraComponent.zoom = 4
    cameraComponent.damping = vec2.new(3,3)
    cameraComponent.forcePosition = true
    local spriteComponent = GameData:createSpriteComponent(entity)
    spriteComponent:setImage("../ExampleGame/Tiles/PlayerGrowthSprites.png", 5, 9, 0, GameData.resourcePool)
    spriteComponent.offset = vec2.new(32,32)
    local spriteAnimationComponent = GameData:createSpriteAnimationComponent(entity)
    local idle8Animation = spriteAnimation.new(0, 4, 1, true)
    local run8Animation = spriteAnimation.new(4, 9, 0.7, true)
    local idle16Animation = spriteAnimation.new(9, 13, 1, true)
    local run16Animation = spriteAnimation.new(13, 18, 0.7, true)
    local idle32Animation = spriteAnimation.new(18, 22, 1, true)
    local run32Animation = spriteAnimation.new(22, 27, 0.7, true)
    local idle64Animation = spriteAnimation.new(27, 31, 1, true)
    local run64Animation = spriteAnimation.new(31, 36, 0.7, true)
    local transformAnimation = spriteAnimation.new(36, 43, 0.6, false)
    spriteAnimationComponent:addAnimation("idle8", idle8Animation)
    spriteAnimationComponent:addAnimation("run8", run8Animation)
    spriteAnimationComponent:addAnimation("idle16", idle16Animation)
    spriteAnimationComponent:addAnimation("run16", run16Animation)
    spriteAnimationComponent:addAnimation("idle32", idle32Animation)
    spriteAnimationComponent:addAnimation("run32", run32Animation)
    spriteAnimationComponent:addAnimation("idle64", idle64Animation)
    spriteAnimationComponent:addAnimation("run64", run64Animation)
    spriteAnimationComponent:addAnimation("transform", transformAnimation)
    spriteAnimationComponent:playAnimation("idle8", systemTime)
    
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    entityTable.Movement = Movement:new()
    entityTable.Movement.registerProperties(entityTable)
    entityTable.transformTime = 10
    entityTable.transforming = false
    --entityTable.timeOfLastTransformation = nil
    entityTable.curSize = "small8"
    entityTable.currentAnimation = "idle"
    entityTable.velocity = vec2.new(0,0)
end
    
PlayerScript.update = function(entity, dt, systemTime)
    local transformComponent = GameData:getTransformComponent(entity)
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    local cameraComponent = GameData:getCameraComponent(entity)
    local spriteComponent = GameData:getSpriteComponent(entity)
    local spriteAnimationComponent = GameData:getSpriteAnimationComponent(entity)
    if not entityTable.transforming then
        local moveInput = GameData.input:getInputAxis("Horizontal")
        local jumpInput = GameData.input:isInputDown("Jump")

        if not entityTable.timeOfLastTransformation then
            entityTable.timeOfLastTransformation = systemTime
        end
        local activeTransformTime = systemTime - entityTable.timeOfLastTransformation
        if entityTable.transformTime < activeTransformTime then
            entityTable.timeOfLastTransformation = nil
            entityTable.transforming = true
        else
            local sizeIndex = 1 + math.floor(#sizes * activeTransformTime / entityTable.transformTime) 
            sizeIndex = math.clamp(sizeIndex, 1, #sizes)
            
            if moveInput ~= 0 then
                if entityTable.currentAnimation ~= "run" then
                    entityTable.currentAnimation = "run"
                end
            elseif entityTable.currentAnimation ~= "idle" then
                entityTable.currentAnimation = "idle"
            end
            local newSize = sizes[sizeIndex]

            local speedMultiplier = speedMultipliers[entityTable.curSize]
            local movement = entityTable.Movement
            movement:setSpeed(entityTable.velocity)

            movement:setHorizontalInput(moveInput)
            movement:setJumpInput(jumpInput, systemTime)
            local groundedRec = groundedRecs[newSize]
            local entityPosition = transformComponent.position
            local isGrounded = tileMapCollision(groundedRec, vec2.new(entityPosition.x, entityPosition.y))
            movement:moveMaxSpeed(entityTable)
            movement:calculateGravity(entityTable, systemTime, dt, isGrounded)
            movement:jump(entityTable, systemTime, dt)
        
            local horizontalSpeed, verticalSpeed = movement:getSpeed()
            entityTable.velocity = vec2.new(horizontalSpeed, verticalSpeed)

            if newSize ~= entityTable.curSize then
                entityTable.curSize = newSize
                
                local collisionRec = collisionRecs[entityTable.curSize]
                local targetPositionX = entityPosition.x
                local targetPositionY = entityPosition.y
                while tileMapCollisionUp(collisionRec, vec2.new(targetPositionX, targetPositionY)) do
                    print("up")
                    targetPositionY = targetPositionY + 0.25
                    if entityTable.velocity.y < 0 then
                        entityTable.velocity.y = 0
                    end
                end
                while tileMapCollisionLeft(collisionRec, vec2.new(targetPositionX, targetPositionY)) do
                    print("Left")
                    targetPositionX = targetPositionX + 0.25
                    if entityTable.velocity.x < 0 then
                        entityTable.velocity.x = 0
                    end
                end
                while tileMapCollisionRight(collisionRec, vec2.new(targetPositionX, targetPositionY)) do
                    print("Right")
                    targetPositionX = targetPositionX - 0.25
                    if entityTable.velocity.x > 0 then
                        entityTable.velocity.x = 0
                    end
                end
                transformComponent.position = vec2.new(targetPositionX, targetPositionY)
            end
            
            local desiredAnimation = playerAnimations[entityTable.curSize][entityTable.currentAnimation]
            if desiredAnimation ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation(desiredAnimation, systemTime)
            end

        end
        if moveInput > 0 then
            spriteComponent.flipped = false
        elseif moveInput < 0 then
            spriteComponent.flipped = true
        end
    else
        if playerAnimations.transform ~= spriteAnimationComponent:getCurAnimation() then
            spriteAnimationComponent:playAnimation(playerAnimations.transform, systemTime)
        elseif not spriteAnimationComponent:isAnimationPlaying(systemTime) then
            entityTable.transforming = false
            cameraComponent:addTrauma(0.5)
        end
    end

    -- calculate collision
    local collisionRec = collisionRecs[entityTable.curSize]
    local initialPosition = transformComponent.position
    local targetPositionX = initialPosition.x + entityTable.velocity.x * dt
    local targetPositionY = initialPosition.y + entityTable.velocity.y * dt
    local horizontalDir = math.sign(entityTable.velocity.x)
    local verticalDir = math.sign(entityTable.velocity.y)
    while tileMapCollision(collisionRec, vec2.new(targetPositionX, initialPosition.y)) and horizontalDir ~= 0 do
        print("Collision Move Left" .. entityTable.velocity.x)
        targetPositionX = targetPositionX - horizontalDir * 0.25
        entityTable.velocity.x = 0
    end
    while tileMapCollision(collisionRec, vec2.new(targetPositionX, targetPositionY))  and verticalDir ~= 0 do
        targetPositionY = targetPositionY - verticalDir * 0.25
        entityTable.velocity.y = 0
    end
    transformComponent.position = vec2.new(targetPositionX, targetPositionY)
end

PlayerScript.destroy = function(entity)

end

return PlayerScript
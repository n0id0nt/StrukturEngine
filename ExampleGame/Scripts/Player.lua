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
        jump = "jump8",
        fall = "fall8",
    },
    medium16 = {
        idle = "idle16",
        run = "run16",
        jump = "jump16",
        fall = "fall16",
    },
    large32 = {
        idle = "idle32",
        run = "run32",
        jump = "jump32",
        fall = "fall32",
    },
    giant64 = {
        idle = "idle64",
        run = "run64",
        jump = "jump64",
        fall = "fall64",
    },
    transform = "transform",
}
local speedFunctions = {
    small8 = function(tableComponent)
        -- move
        tableComponent.accelerationTime = 0.3
        tableComponent.deccelerationTime = 0.2
        tableComponent.maxSpeed = 40
        -- jump
        tableComponent.jumpDist         = 1.2 * 16
        tableComponent.jumpHeight       = 2.2 * 16
        tableComponent.jumpFallDist     = 2   * 16
    end,
    medium16 = function(tableComponent)
        -- move
        tableComponent.accelerationTime = 0.3
        tableComponent.deccelerationTime = 0.2
        tableComponent.maxSpeed = 55
        -- jump
        tableComponent.jumpDist         = 2.2 * 16
        tableComponent.jumpHeight       = 3.5 * 16
        tableComponent.jumpFallDist     = 2   * 16
    end,
    large32 = function(tableComponent)
        -- move
        tableComponent.accelerationTime = 0.3
        tableComponent.deccelerationTime = 0.2
        tableComponent.maxSpeed = 80
        -- jump
        tableComponent.jumpDist         = 3.2 * 16
        tableComponent.jumpHeight       = 4.5 * 16
        tableComponent.jumpFallDist     = 2   * 16
    end,
    giant64 = function(tableComponent)
        -- move
        tableComponent.accelerationTime = 0.3
        tableComponent.deccelerationTime = 0.2
        tableComponent.maxSpeed = 65
        -- jump
        tableComponent.jumpDist         = 2.7 * 16
        tableComponent.jumpHeight       = 3.5 * 16
        tableComponent.jumpFallDist     = 2   * 16
    end,
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

local function rectToRectCollision(r1, r2)
    local r1RightR2Left = r1.x + r1.width >= r2.x
    local r1LeftR2Right = r1.x <= r2.x + r2.width
    local r1TopR2Bottom = r1.y + r1.height >= r2.y
    local r1BottomR2Top = r1.y <= r2.y + r2.height

    return r1RightR2Left and r1LeftR2Right and r1TopR2Bottom and r1BottomR2Top
end

local function huskCollision(preCollisionRec, postCollisionRec, prePosition, postPosition)
    --print("Husk Collision Check")
    local huskEntities = GameData:getEntitiesWithIdentifier("PlayerHusk")
    local positionedPreCollisionRec = rectangle.new(preCollisionRec.x + prePosition.x, preCollisionRec.y + prePosition.y, preCollisionRec.width, preCollisionRec.height)
    local positionedPostCollisionRec = rectangle.new(postCollisionRec.x + postPosition.x, postCollisionRec.y + postPosition.y, postCollisionRec.width, postCollisionRec.height)
    for _, huskEntity in ipairs(huskEntities) do
        local huskTransformComponent = GameData:getTransformComponent(huskEntity)
        local huskPosition = huskTransformComponent.position
        local huskLuaComponent = GameData:getLuaComponent(huskEntity)
        local huskCollisionRec = huskLuaComponent.table.collisionRec
        local huskPositionedCollisionRec = rectangle.new(huskCollisionRec.x + huskPosition.x, huskCollisionRec.y + huskPosition.y, huskCollisionRec.width, huskCollisionRec.height)
        local initialCollision = rectToRectCollision(positionedPreCollisionRec, huskPositionedCollisionRec)
        local finalCollision = rectToRectCollision(positionedPostCollisionRec, huskPositionedCollisionRec)
        --print("initialCollision " )
        --print(initialCollision)
        --print("x: " .. positionedPreCollisionRec.x .. " y: " .. positionedPreCollisionRec.y .. " width: " .. positionedPreCollisionRec.width .. " height: " .. positionedPreCollisionRec.height)
        --print("x: " .. prePosition.x .. " y: " .. prePosition.y)
        --print("finalCollision ")
        --print(finalCollision)
        --rint("x: " .. positionedPostCollisionRec.x .. " y: " .. positionedPostCollisionRec.y .. " width: " .. positionedPostCollisionRec.width .. " height: " .. positionedPostCollisionRec.height)
        --rint("x: " .. postPosition.x .. " y: " .. postPosition.y)
        --rint("huskCollision ")
        --rint("x: " .. huskPositionedCollisionRec.x .. " y: " .. huskPositionedCollisionRec.y .. " width: " .. huskPositionedCollisionRec.width .. " height: " .. huskPositionedCollisionRec.height)
        --rint("x: " .. huskPosition.x .. " y: " .. huskPosition.y)
        if not initialCollision and finalCollision and huskPosition.y > positionedPreCollisionRec.y + positionedPreCollisionRec.height then
            --print("Husk Check")
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
    spriteComponent:setImage("../ExampleGame/Tiles/PlayerGrowthSprites.png", 5, 12, 0, GameData.resourcePool)
    spriteComponent.offset = vec2.new(32,32)
    local spriteAnimationComponent = GameData:createSpriteAnimationComponent(entity)
    local idle8Animation = spriteAnimation.new(0, 4, 1, true)
    local run8Animation = spriteAnimation.new(4, 9, 0.7, true)
    local jump8Animation = spriteAnimation.new(9, 11, 0.2, false)
    local fall8Animation = spriteAnimation.new(11, 12, 1, false)

    local idle16Animation = spriteAnimation.new(12, 16, 1, true)
    local run16Animation = spriteAnimation.new(16, 21, 0.7, true)
    local jump16Animation = spriteAnimation.new(21, 23, 0.2, false)
    local fall16Animation = spriteAnimation.new(23, 24, 1, false)

    local idle32Animation = spriteAnimation.new(24, 28, 1, true)
    local run32Animation = spriteAnimation.new(28, 33, 0.7, true)
    local jump32Animation = spriteAnimation.new(33, 35, 0.2, false)
    local fall32Animation = spriteAnimation.new(35, 36, 1, false)

    local idle64Animation = spriteAnimation.new(36, 40, 1, true)
    local run64Animation = spriteAnimation.new(40, 45, 0.7, true)
    local jump64Animation = spriteAnimation.new(45, 47, 0.2, false)
    local fall64Animation = spriteAnimation.new(47, 48, 1, false)

    local transformAnimation = spriteAnimation.new(48, 55, 0.6, false)

    spriteAnimationComponent:addAnimation("idle8", idle8Animation)
    spriteAnimationComponent:addAnimation("run8", run8Animation)
    spriteAnimationComponent:addAnimation("jump8", jump8Animation)
    spriteAnimationComponent:addAnimation("fall8", fall8Animation)

    spriteAnimationComponent:addAnimation("idle16", idle16Animation)
    spriteAnimationComponent:addAnimation("run16", run16Animation)
    spriteAnimationComponent:addAnimation("jump16", jump16Animation)
    spriteAnimationComponent:addAnimation("fall16", fall16Animation)
    
    spriteAnimationComponent:addAnimation("idle32", idle32Animation)
    spriteAnimationComponent:addAnimation("run32", run32Animation)
    spriteAnimationComponent:addAnimation("jump32", jump32Animation)
    spriteAnimationComponent:addAnimation("fall32", fall32Animation)
    
    spriteAnimationComponent:addAnimation("idle64", idle64Animation)
    spriteAnimationComponent:addAnimation("run64", run64Animation)
    spriteAnimationComponent:addAnimation("jump64", jump64Animation)
    spriteAnimationComponent:addAnimation("fall64", fall64Animation)
    
    spriteAnimationComponent:addAnimation("transform", transformAnimation)

    spriteAnimationComponent:playAnimation("idle8", systemTime)
    
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    entityTable.Movement = Movement:new()
    entityTable.transformTime = 10
    entityTable.transforming = false
    --entityTable.timeOfLastTransformation = nil
    entityTable.curSize = "small8"
    entityTable.currentAnimation = "idle"
    entityTable.velocity = vec2.new(0,0)
    entityTable.bufferTime       = 0.08
    entityTable.coyoteTime       = 0.08
    entityTable.maxFallSpeed     = 130
    speedFunctions[entityTable.curSize](entityTable)
end
    
PlayerScript.update = function(entity, dt, systemTime)
    local transformComponent = GameData:getTransformComponent(entity)
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    local cameraComponent = GameData:getCameraComponent(entity)
    local spriteComponent = GameData:getSpriteComponent(entity)
    local spriteAnimationComponent = GameData:getSpriteAnimationComponent(entity)
    if not entityTable.transforming then
        local horizontalInput = GameData.input:getInputAxis("Horizontal")
        local jumpInput = GameData.input:isInputDown("Jump")

        if not entityTable.timeOfLastTransformation then
            entityTable.timeOfLastTransformation = systemTime
        end
        local activeTransformTime = systemTime - entityTable.timeOfLastTransformation
        if entityTable.transformTime < activeTransformTime then
            entityTable.timeOfLastTransformation = nil
            entityTable.transforming = true
            entityTable.velocity = vec2.new(0,0)
        else
            local sizeIndex = 1 + math.floor(#sizes * activeTransformTime / entityTable.transformTime) 
            sizeIndex = math.clamp(sizeIndex, 1, #sizes)
            
            local newSize = sizes[sizeIndex]

            local movement = entityTable.Movement
            movement:setSpeed(entityTable.velocity)

            movement:setHorizontalInput(horizontalInput)
            movement:setJumpInput(jumpInput, systemTime)
            local groundedRec = groundedRecs[newSize]
            local collisionRec = collisionRecs[newSize]
            local entityPosition = transformComponent.position
            local isGroundedTileMap = tileMapCollision(groundedRec, entityPosition)
            local isGroundedHusk = huskCollision(collisionRec, groundedRec, entityPosition, entityPosition)
            local isGrounded = isGroundedTileMap or isGroundedHusk
            movement:move(entityTable, systemTime, dt)
            movement:calculateGravity(entityTable, systemTime, dt, isGrounded)
            movement:jump(entityTable, systemTime, dt)
        
            local horizontalSpeed, verticalSpeed = movement:getSpeed()
            entityTable.velocity = vec2.new(horizontalSpeed, verticalSpeed)

            if isGrounded then
                if horizontalInput ~= 0 then
                    entityTable.currentAnimation = "run"
                else
                    entityTable.currentAnimation = "idle"
                end
            else
                if movement.verticalSpeed < 0 then
                    entityTable.currentAnimation = "jump"
                else
                    entityTable.currentAnimation = "fall"
                end
            end

            if newSize ~= entityTable.curSize then
                cameraComponent:addTrauma(0.3)
                entityTable.curSize = newSize
                speedFunctions[newSize](entityTable)
                local targetPositionX = entityPosition.x
                local targetPositionY = entityPosition.y
                while tileMapCollisionUp(collisionRec, vec2.new(targetPositionX, targetPositionY)) do
                    targetPositionY = targetPositionY + 0.25
                    if entityTable.velocity.y < 0 then
                        entityTable.velocity.y = 0
                    end
                end
                while tileMapCollisionLeft(collisionRec, vec2.new(targetPositionX, targetPositionY)) do
                    targetPositionX = targetPositionX + 0.25
                    if entityTable.velocity.x < 0 then
                        entityTable.velocity.x = 0
                    end
                end
                while tileMapCollisionRight(collisionRec, vec2.new(targetPositionX, targetPositionY)) do
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
        if horizontalInput > 0 then
            spriteComponent.flipped = false
        elseif horizontalInput < 0 then
            spriteComponent.flipped = true
        end
    else
        if playerAnimations.transform ~= spriteAnimationComponent:getCurAnimation() then
            spriteAnimationComponent:playAnimation(playerAnimations.transform, systemTime)
        elseif not spriteAnimationComponent:isAnimationPlaying(systemTime) then
            entityTable.transforming = false
            cameraComponent:addTrauma(0.45)
            local huskEntities = GameData:getEntitiesWithIdentifier("PlayerHusk")
            for _, huskEntity in ipairs(huskEntities) do
                local huskTransformComponent = GameData:getTransformComponent(huskEntity)
                local huskSpriteComponent = GameData:getSpriteComponent(huskEntity)

                huskTransformComponent.position = transformComponent.position
                huskSpriteComponent.flipped = spriteComponent.flipped
            end
        end
    end

    -- calculate collision
    local collisionRec = collisionRecs[entityTable.curSize]
    local initialPosition = transformComponent.position
    local targetPositionX = initialPosition.x + entityTable.velocity.x * dt
    local targetPositionY = initialPosition.y + entityTable.velocity.y * dt
    local horizontalDir = math.sign(entityTable.velocity.x)
    local verticalDir = math.sign(entityTable.velocity.y)
    while horizontalDir ~= 0 and tileMapCollision(collisionRec, vec2.new(targetPositionX, initialPosition.y)) do
        targetPositionX = targetPositionX - horizontalDir * 0.25
        entityTable.velocity.x = 0
    end
    while verticalDir ~= 0 and tileMapCollision(collisionRec, vec2.new(targetPositionX, targetPositionY))  do
        targetPositionY = targetPositionY - verticalDir * 0.25
        entityTable.velocity.y = 0
    end
    while verticalDir > 0 and huskCollision(collisionRec, collisionRec, initialPosition, vec2.new(targetPositionX, targetPositionY)) do
        targetPositionY = targetPositionY - verticalDir * 0.25
        --print(targetPositionY)
        entityTable.velocity.y = 0
    end
    --while horizontalDir ~= 0 and huskCollision(collisionRec, initialPosition, vec2.new(targetPositionX, targetPositionY)) do
    --    targetPositionX = targetPositionX - horizontalDir * 0.25
    --    --print(targetPositionY)
    --    entityTable.velocity.x = 0
    --end
    transformComponent.position = vec2.new(targetPositionX, targetPositionY)
end

PlayerScript.destroy = function(entity)

end

return PlayerScript
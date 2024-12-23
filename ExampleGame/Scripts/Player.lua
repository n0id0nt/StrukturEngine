local Movement = require("Movement")

local PlayerScript = {} -- scriptTemplate.new()

local jumpSound = "../ExampleGame/Sounds/jumpMedium.wav"
-- should put these on the players table
local playerAnimations = {
    idle = "idle32",
    run = "run32",
    jump = "jump32",
    fall = "fall32",
}
local speedFunction = function(tableComponent)
    -- move
    tableComponent.accelerationTime = 0.3
    tableComponent.deccelerationTime= 0.2
    tableComponent.maxSpeed         = 80
    -- jump
    tableComponent.jumpDist         = 3.2 * 16
    tableComponent.jumpHeight       = 4.5 * 16
    tableComponent.jumpFallDist     = 2   * 16
end
local collisionRec = rectangle.new(-6,32-30,12,30)

local groundedRec = rectangle.new(-6,32,12,0.25)

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
        if not initialCollision and finalCollision and huskPosition.y > positionedPreCollisionRec.y + positionedPreCollisionRec.height then
            return true
        end
    end
    return false
end

local function pastCutScene(playerPosition)
    local entities = GameData:getEntitiesWithIdentifier("CutScene")
    for _, entity in ipairs(entities) do
        local luaComponent = GameData:getLuaComponent(entity)
        local luaTable = luaComponent.table
        if not luaTable.cutSceneHandled then
            local transformComponent = GameData:getTransformComponent(entity)
            if transformComponent.position.x < playerPosition.x then
                luaTable.cutSceneHandled = true
                print("Playing cut scene " .. luaTable.CutSceneIndex)
                GameData.cutSceneIndex = luaTable.CutSceneIndex
                return true
            end
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

    local idle32Animation = spriteAnimation.new(24, 28, 1, true)
    local run32Animation = spriteAnimation.new(28, 33, 0.7, true)
    local jump32Animation = spriteAnimation.new(33, 35, 0.2, false)
    local fall32Animation = spriteAnimation.new(35, 36, 1, false)
    
    spriteAnimationComponent:addAnimation("idle32", idle32Animation)
    spriteAnimationComponent:addAnimation("run32", run32Animation)
    spriteAnimationComponent:addAnimation("jump32", jump32Animation)
    spriteAnimationComponent:addAnimation("fall32", fall32Animation)
    spriteAnimationComponent:playAnimation("idle32", systemTime)
    
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    entityTable.movement = Movement:new()
    entityTable.transformTime = 10
    entityTable.transforming = false
    entityTable.currentAnimation = "idle"
    entityTable.velocity = vec2.new(0,0)
    entityTable.bufferTime       = 0.08
    entityTable.coyoteTime       = 0.08
    entityTable.maxFallSpeed     = 130
    speedFunction(entityTable)
end
    
PlayerScript.update = function(entity, dt, systemTime)
    local transformComponent = GameData:getTransformComponent(entity)
    local luaComponent = GameData:getLuaComponent(entity)
    local entityTable = luaComponent.table
    local cameraComponent = GameData:getCameraComponent(entity)
    local spriteComponent = GameData:getSpriteComponent(entity)
    local spriteAnimationComponent = GameData:getSpriteAnimationComponent(entity)
    local isGrounded
    if not entityTable.transforming then
        local horizontalInput = GameData.input:getInputAxis("Horizontal")
        local jumpInput = GameData.input:isInputDown("Jump")
        local movement = entityTable.movement
        movement:setHorizontalInput(horizontalInput)
        movement:setJumpInput(jumpInput, systemTime)
        local entityPosition = transformComponent.position
        local isGroundedTileMap = tileMapCollision(groundedRec, entityPosition)
        local isGroundedHusk = huskCollision(collisionRec, groundedRec, entityPosition, entityPosition)
        isGrounded = isGroundedTileMap or isGroundedHusk
        movement:move(entityTable, systemTime, dt)
        movement:calculateGravity(entityTable, systemTime, dt, isGrounded)
        movement:jump(entityTable, systemTime, dt)

        if movement.justJumped then
            GameData:playSound(jumpSound)
        end
    
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
        
        local desiredAnimation = playerAnimations[entityTable.currentAnimation]
        if desiredAnimation ~= spriteAnimationComponent:getCurAnimation() then
            spriteAnimationComponent:playAnimation(desiredAnimation, systemTime)
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

    if isGrounded and pastCutScene(transformComponent.position) then
        GameData.gameState = eGameState.CutScene
    end
    --while horizontalDir ~= 0 and huskCollision(collisionRec, initialPosition, vec2.new(targetPositionX, targetPositionY)) do
    --    targetPositionX = targetPositionX - horizontalDir * 0.25
    --    --print(targetPositionY)
    --    entityTable.velocity.x = 0
    --end
    transformComponent.position = vec2.new(targetPositionX, targetPositionY)
    --print("x: " .. transformComponent.position.x .. " y: " .. transformComponent.position.y)

end

PlayerScript.destroy = function(entity)

end

return PlayerScript
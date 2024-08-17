local PlayerScript = scriptTemplate.new()

local sizes = {
    "small8",
    "medium16",
    "large32",
    "giant64",
}
-- should put these on the players table
local transformTime = 10
local transforming = false
local timeOfLastTransformation
local curSize = "small8"
local currentAnimation
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
    small8 = rectangle.new(-2,32-8,3,7),
    medium16 = rectangle.new(-3,32-16,5,15),
    large32 = rectangle.new(-6,32-32,11,31),
    giant64 = rectangle.new(-11,32-64,21,63),
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
    currentAnimation = "idle"
end
    
PlayerScript.update = function(entity, dt, systemTime)
    local velocityX = 0
    local velocityY = 0
    local transformComponent = GameData:getTransformComponent(entity)
    local luaComponent = GameData:getLuaComponent(entity)
    local cameraComponent = GameData:getCameraComponent(entity)
    local spriteComponent = GameData:getSpriteComponent(entity)
    local spriteAnimationComponent = GameData:getSpriteAnimationComponent(entity)
    local speed = luaComponent.table.MaxSpeed
    if not transforming then
        local moveInput = GameData.input:getInputAxis("Horizontal")
        local scaleInput = GameData.input:getInputAxis("Vertical")
        --transformComponent.scale = transformComponent.scale.y + scaleInput * speed * dt
        --transformComponent.translation.y = transformComponent.translation.y - moveInput.y * speed * dt
        if not timeOfLastTransformation then
            timeOfLastTransformation = systemTime
        end
        local activeTransformTime = systemTime - timeOfLastTransformation
        if transformTime < activeTransformTime then
            timeOfLastTransformation = nil
            transforming = true
        else
            local sizeIndex = 1 + math.floor(#sizes * activeTransformTime / transformTime) 
            sizeIndex = math.clamp(sizeIndex, 1, #sizes)
            
            if moveInput ~= 0 then
                if currentAnimation ~= "run" then
                    currentAnimation = "run"
                end
            elseif currentAnimation ~= "idle" then
                currentAnimation = "idle"
            end
            curSize = sizes[sizeIndex]
            --TODO When the size changes add a check for collision
            
            local desiredAnimation = playerAnimations[curSize][currentAnimation]
            if desiredAnimation ~= spriteAnimationComponent:getCurAnimation() then
                spriteAnimationComponent:playAnimation(desiredAnimation, systemTime)
            end

            local speedMultiplier = speedMultipliers[curSize]
            velocityX = moveInput * speed * dt * speedMultiplier
            velocityY = scaleInput * speed * dt * speedMultiplier
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
            transforming = false
            cameraComponent:addTrauma(0.5)
        end
    end

    -- calculate collision
    local collisionRec = collisionRecs[curSize]
    local initialPosition = transformComponent.position
    local targetPositionX = math.round(initialPosition.x + velocityX)
    local targetPositionY = math.round(initialPosition.y + velocityY)
    while tileMapCollision(collisionRec, vec2.new(targetPositionX, initialPosition.y)) and velocityX ~= 0 do
        targetPositionX = targetPositionX - math.sign(velocityX)
    end
    while tileMapCollision(collisionRec, vec2.new(targetPositionX, targetPositionY))  and velocityY ~= 0 do
        targetPositionY = targetPositionY - math.sign(velocityY)
    end
    transformComponent.position = vec2.new(targetPositionX, targetPositionY)
end

PlayerScript.destroy = function(entity)

end

return PlayerScript
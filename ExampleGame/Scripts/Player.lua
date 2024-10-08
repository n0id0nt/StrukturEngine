local PlayerScript = scriptTemplate.new()

PlayerScript.create = function(entity, dt, systemTime)
    print("Create Player")
    local cameraComponent = GameData:createCameraComponent(entity)
    cameraComponent.cameraPriority = 1
    cameraComponent.zoom = 3
    cameraComponent.damping = vec2.new(3,3)
    cameraComponent.forcePosition = true
    local spriteComponent = GameData:createSpriteComponent(entity)
    spriteComponent:setImage("../ExampleGame/Tiles/Warrior_Sheet-Effect.png", 17, 6, 0, GameData.resourcePool)
    local spriteAnimationComponent = GameData:createSpriteAnimationComponent(entity)
    local idleAnimation = spriteAnimation.new(0, 6, 1, true)
    local runAnimation = spriteAnimation.new(7, 14, 1, true)
    spriteAnimationComponent:addAnimation("idle", idleAnimation)
    spriteAnimationComponent:addAnimation("run", runAnimation)
    spriteAnimationComponent:playAnimation("idle", systemTime)
end
    
PlayerScript.update = function(entity, dt, systemTime)
    local transformComponent = GameData:getTransformComponent(entity)
    local luaComponent = GameData:getLuaComponent(entity)
    local cameraComponent = GameData:getCameraComponent(entity)
    local spriteComponent = GameData:getSpriteComponent(entity)
    local spriteAnimationComponent = GameData:getSpriteAnimationComponent(entity)
    local speed = luaComponent.table.MaxSpeed
    local moveInput = GameData.input:getInputAxis("Horizontal")
    local scaleInput = GameData.input:getInputAxis("Vertical")
    transformComponent.position = vec2.new(transformComponent.position.x + moveInput * speed * dt, transformComponent.position.y + scaleInput * speed * dt)
    transformComponent.scale = vec2.new(2, 2)
    --transformComponent.scale = transformComponent.scale.y + scaleInput * speed * dt
    --transformComponent.translation.y = transformComponent.translation.y - moveInput.y * speed * dt
    if moveInput ~= 0 then
        if spriteAnimationComponent:getCurAnimation() ~= "run" then
            spriteAnimationComponent:playAnimation("run", systemTime)
        end
    elseif spriteAnimationComponent:getCurAnimation() ~= "idle" then
        spriteAnimationComponent:playAnimation("idle", systemTime)
    end

    if moveInput > 0 then
        spriteComponent.flipped = false
    elseif moveInput < 0 then
        spriteComponent.flipped = true
    end

    if GameData.input:isInputDown("Jump") then
        cameraComponent:addTrauma(0.15)
    end
end

PlayerScript.destroy = function(entity)

end

return PlayerScript
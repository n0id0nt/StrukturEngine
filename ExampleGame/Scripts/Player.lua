local Helper_Functions = require("HelperFunctions")
local Movement = require("Movement")
local State_Machine = require("StateMachine")
local Move_State = require("MoveState")
local Dash_State = require("DashState")
local Wall_Slide_State = require("WallSlideState")
local Wall_Jump_State = require("WallJumpState")
local Climb_State = require("ClimbState")

Movement.registerProperties(Script)
local movement = Movement:new()

-- params are a set of shared variable across all states
local params = {
    ladder = 0
}

--------------------------------------------------------------
--ANIMATION
--------------------------------------------------------------
local animations = {
    run = "Run",
    dash = "Dash",
    idle = "Idle",
    jump = "Jump",
    upToFall = "UpToFall",
    fall = "Fall",
    wallSlide = "WallSlide",
    climb = "Climb",
}

function tryPlayAnimation(animation)
    local spriteAnimation = GO:getSpriteAnimation()
    if spriteAnimation:getCurrentAnimation() ~= animation then
        spriteAnimation:playAnimation(animation)
    end
end

--------------------------------------------------------------
--INPUT
--------------------------------------------------------------
local input = {
    horizontalInput = 0,
    jumpInput = false,
}

local function getControllerInput()
    input.horizontalInput = Input:getInputAxis("Horizontal")
    input.verticalInput = Input:getInputAxis("Vertical")
    input.jumpInput = Input:isInputDown("Jump")
end

--------------------------------------------------------------
--STATES
--------------------------------------------------------------
local stateMachine = State_Machine:new()

local states = {
    moveState = Move_State:new(stateMachine, movement, animations, tryPlayAnimation, input, params),
    dashState = Dash_State:new(stateMachine, movement, animations, tryPlayAnimation, input, params),
    wallSlideState = Wall_Slide_State:new(stateMachine, movement, animations, tryPlayAnimation, input, params),
    wallJumpState = Wall_Jump_State:new(stateMachine, movement, animations, tryPlayAnimation, input, params),
    climbState = Climb_State:new(stateMachine, movement, animations, tryPlayAnimation, input, params),
}

stateMachine.states = states
stateMachine:changeState(states.moveState)

--------------------------------------------------------------
--CAMERA
--------------------------------------------------------------
Script:property("cameraLookAhead", 0.3)
Script:property("cameraGroundedOffset", vec2.new(0, -0.3))
Script:property("cameraInAirOffset", vec2.new(0, -0.1))
Script:property("CameraGroundedDeadZone", vec2.new(0, 0))
Script:property("CameraInAirDeadZone", vec2.new(0, 0.4))

function updateCamera()
    local offset = vec2.copy(movement.isGrounded and cameraGroundedOffset or cameraInAirOffset)
    local deadZone = vec2.copy(movement.isGrounded and CameraGroundedDeadZone or CameraInAirDeadZone)
    if input.horizontalInput > 0 then
        offset.x = offset.x - cameraLookAhead
    elseif input.horizontalInput < 0 then
        offset.x = offset.x + cameraLookAhead
    end
    local camera = GO:getCamera()
    camera:setDeadZone(deadZone)
    camera:setOffset(offset)
end

--------------------------------------------------------------
--SCRIPT EVENTS
--------------------------------------------------------------
Script.update = function()
    getControllerInput()

    local velocity = GO:getPhysicsBody():getVelocity()
    movement:setSpeed(velocity.x, velocity.y)

    stateMachine:update()

    local horizontalSpeed, verticalSpeed = movement:getSpeed()
    GO:getPhysicsBody():setVelocity(vec2.new(horizontalSpeed, verticalSpeed))

    updateCamera()

    if Input:isInputJustPressed("Shoot") then 
        Messenger:send('damage', 'Test', GO)
        print("Shoot")
        --local potion = Scene:createTemplatedObject("Template/Potion.tx")
        --local transform = potion:getTransform()
        --transform:setWorldPosition(GO:getTransform():getWorldPosition())
    end

    -- test for loading in and out levels
    -- get the level the player is in
    local position = GO:getTransform():getWorldPosition()
    local levelGO = World:findLevelWithPosition(position)
    if levelGO then
        local level = levelGO:getLevel()
        -- check if the level is currently loaded
        if not level.loaded then
            print("Load level: " .. level.fileName)
            -- load in the new level
            local levelToLoad = levelGO
            -- unload other level (after delay???)
            local levels = World:getLevelEntities()
            for _,levelGO in ipairs(levels) do
                local level = levelGO:getLevel()
                if level and level.loaded then
                    print("Unload level: " .. level.fileName)
                    World:unloadLevel(levelGO)
                end
            end
            World:loadLevel(levelToLoad)
        end
    end
end

Script.onCollisionEnter = function(contact)
    print(contact and contact.other:getName() or "No Name", "Collision Begin")
    if contact and contact.other:hasTag("Ladder") then
        params.ladder = params.ladder + 1
        print("Ladder Collision Enter", params.ladder)
    end
end

Script.onCollisionExit = function(contact)
    print(contact and contact.other:getName() or "No Name", "Collision End")
    if contact and contact.other:hasTag("Ladder") then
        params.ladder = params.ladder - 1
        print("Ladder Collision exit", params.ladder)
    end
end

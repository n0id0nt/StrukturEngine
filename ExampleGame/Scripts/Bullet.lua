local speed = 80
local groundAngle = 30
local gravity = 200 

local hit = false

Script.update = function()
    if hit then return end

    local verticalSpeed = GO:getPhysicsBody():getVelocity().y;
    --print("old speed ", verticalSpeed)
	local horrizontalSpeed = 0;

    local horrizontalDir = 1
    --print("input dir ", horrizontalDir)
    local horrizontalSpeed = horrizontalDir * speed

    local isGrounded = GO:getPhysicsBody():checkGrounded(groundAngle)
    --print("grounded ", isGrounded)
    if not isGrounded then 
        verticalSpeed = verticalSpeed + gravity * Time:getDeltaTime()
    else
        speed = 0
    end

    GO:getPhysicsBody():setVelocity(vec2.new(horrizontalSpeed, verticalSpeed))
end

Script.onCollisionEnter = function(contact)
    if hit then return end
    hit = true

    print(contact.other:getName() or "No Name", "Collision Begin Bullet", "at", contact.velocity, "normal", "x", contact.normal.x, "y", contact.normal.y)
    for i, point in ipairs(contact.contactPoints) do
        print("\tPoint", i, "x", point.x, "y", point.y)
        print("\tImpulse", i, contact.impulses[i])
    end
end
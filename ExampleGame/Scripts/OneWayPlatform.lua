

Script.update = function()
    if Input:isKeyJustReleased("e") then
        local collisionBody = GO:getTileMapCollisionBodyComponent()
        local newValue = not collisionBody:getIsSensor()
        print("platform switch", newValue)
        collisionBody:setIsSensor(newValue)
    end
end

Script.onCollisionPreSolve = function(contact)
    local otherEntity = contact.other
    local otherPhysicsBody = otherEntity:getPhysicsBody()
    if otherPhysicsBody then
        local lowestY = contact:getLowestPointOfFixture()
        local otherHighestY = contact:getHighestPointOfOtherFixture()
        if otherHighestY > lowestY then
            print("other physics")
            contact.enabled = false
        end
    end
end
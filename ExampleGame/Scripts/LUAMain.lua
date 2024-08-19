
local Player_Script = require("Player")
local PlayerHusk_Script = require("PlayerHusk")
local Wizzard_Script = require("Wizzard")
local CutScene = require("CutScene")

local gameObjects = 
{
    Player = Player_Script,
    PlayerHusk = PlayerHusk_Script,
    Wizzard = Wizzard_Script,
} 

Script.initialise = function(systemTime)
    -- initialise each component
    for objectIdentifier, script in pairs(gameObjects) do
        local entities = GameData:getEntitiesWithIdentifier(objectIdentifier)
        for _, entity in ipairs(entities) do
            script.create(entity, 0, systemTime)
            local luaComponent = GameData:getLuaComponent(entity)
            luaComponent.initalised = true
        end
    end
end

Script.update = function(dt, systemTime)
    if GameData.gameState ~= eGameState.MainMenu and GameData.input:isInputJustReleased("Pause") then
        GameData.gameState, GameData.previousGameState = GameData.previousGameState, GameData.gameState
    end
    if GameData.gameState == eGameState.Game then
        for objectIdentifier, script in pairs(gameObjects) do
            local entities = GameData:getEntitiesWithIdentifier(objectIdentifier)
            for _, entity in ipairs(entities) do
                local luaComponent = GameData:getLuaComponent(entity)
                if not luaComponent.initalised then
                    script.create(entity)
                    luaComponent.initalised = true
                end
                
                script.update(entity, dt, systemTime)
            end
        end
    elseif GameData.gameState == eGameState.CutScene then
        CutScene:update(dt, systemTime)
    end
end

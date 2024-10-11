
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

local gameStateSongs = 
{
    [eGameState.MainMenu] = "../ExampleGame/Sounds/menuMusic.wav",
    [eGameState.Game] = "../ExampleGame/Sounds/gameMusic.wav",
    [eGameState.CutScene] = "../ExampleGame/Sounds/gameMusic.wav",
    [eGameState.Pause] = "../ExampleGame/Sounds/menuMusic.wav",
}

local currentSong

Script.initialise = function(systemTime)
    -- initialise each component
    for objectIdentifier, script in pairs(gameObjects) do
        local entities = GameData:getEntitiesWithIdentifier(objectIdentifier)
        for _, entity in ipairs(entities) do
            script.create(entity, 0, systemTime)
            local luaComponent = GameData:getLuaComponent(entity)
            luaComponent.initalised = true
            print(objectIdentifier)
        end
    end
end

Script.update = function(dt, systemTime)
    if currentSong ~= gameStateSongs[GameData.gameState] then
        if currentSong then
            GameData:stopSound(currentSong)
        end
        currentSong = gameStateSongs[GameData.gameState]
        GameData:playSound(currentSong)
    elseif not GameData:isSoundPlaying(currentSong) then
        GameData:playSound(currentSong)
    end
    
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

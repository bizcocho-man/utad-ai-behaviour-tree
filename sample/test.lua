MOAISim.openWindow("game", 1024, 768)

viewport = MOAIViewport.new()
viewport:setSize (1024, 768)
viewport:setScale (1024, -768)

layer = MOAILayer2D.new()
layer:setViewport(viewport)
MOAISim.pushRenderPass(layer)

function drawBackground(image, sizeX, sizeY)
    gfxQuad = MOAIGfxQuad2D.new()
    gfxQuad:setTexture(image)
    gfxQuad:setRect(-sizeX/2, -sizeY/2, sizeX/2, sizeY/2)
    gfxQuad:setUVRect(0, 0, 1, 1)
    prop = MOAIProp2D.new()
    prop:setDeck(gfxQuad)
    prop:setLoc(posX, posY)
    layer:insertProp(prop)
end

player = Character.new()

-- Idle image
gfxQuadIdle = MOAIGfxQuad2D.new()
gfxQuadIdle:setTexture("dragon_idle.png")
gfxQuadIdle:setRect(-45, -50, 45, 50)
gfxQuadIdle:setUVRect(0, 0, 1, 1)
player:addImage(gfxQuadIdle)
player:addImageName("dragon_idle.png")

-- Alert image
gfxQuadAlert = MOAIGfxQuad2D.new()
gfxQuadAlert:setTexture("dragon_alert.png")
gfxQuadAlert:setRect(-45, -50, 45, 50)
gfxQuadAlert:setUVRect(0, 0, 1, 1)
player:addImage(gfxQuadAlert)
player:addImageName("dragon_alert.png")

-- Moving image
gfxQuadMoving = MOAIGfxQuad2D.new()
gfxQuadMoving:setTexture("dragon_moving.png")
gfxQuadMoving:setRect(-45, -50, 45, 50)
gfxQuadMoving:setUVRect(0, 0, 1, 1)
player:addImage(gfxQuadMoving)
player:addImageName("dragon_moving.png")

-- Prepare attack image
gfxQuadPrepareAttack = MOAIGfxQuad2D.new()
gfxQuadPrepareAttack:setTexture("dragon_prepare_attack.png")
gfxQuadPrepareAttack:setRect(-45, -50, 45, 50)
gfxQuadPrepareAttack:setUVRect(0, 0, 1, 1)
player:addImage(gfxQuadPrepareAttack)
player:addImageName("dragon_prepare_attack.png")

-- Attack image
gfxQuadAttack = MOAIGfxQuad2D.new()
gfxQuadAttack:setTexture("dragon_attack.png")
gfxQuadAttack:setRect(-45, -50, 45, 50)
gfxQuadAttack:setUVRect(0, 0, 1, 1)
player:addImage(gfxQuadAttack)
player:addImageName("dragon_attack.png")

-- Pain image
gfxQuadPain = MOAIGfxQuad2D.new()
gfxQuadPain:setTexture("dragon_pain.png")
gfxQuadPain:setRect(-45, -50, 45, 50)
gfxQuadPain:setUVRect(0, 0, 1, 1)
player:addImage(gfxQuadPain)
player:addImageName("dragon_pain.png")
  
prop = MOAIProp2D.new()
prop:setDeck(gfxQuadIdle)

-- Add prop to be the renderable for this character
player:setProp(prop, layer)
-- Start the character (allow calls to OnUpdate)
player:start()
player:setLoc(0, 0)
player:setRot(0)
player:setLinearVel(10, 20)
player:setAngularVel(30)
player:readAndInitializeBehaviorTree("behaviortree.xml")

-- Enable Debug Draw
debug = MOAIDrawDebug.get();
layer:setDrawDebug(debug)
-- Add this character to draw debug
MOAIDrawDebug.insertEntity(player)


--pathfinder = Pathfinder.new()

--pathfinder:setStartPosition(5, 10)
--pathfinder:setEndPosition(20, 40)
--MOAIDrawDebug.insertEntity(pathfinder)

mouseX = 0
mouseY = 0

function onClick(down)
  if down == true then
	enemy = Character.new()

	-- Idle image
	gfxQuadMageIdle = MOAIGfxQuad2D.new()
	gfxQuadMageIdle:setTexture("mage_idle.png")
	gfxQuadMageIdle:setRect(-25, -45, 25, 45)
	gfxQuadMageIdle:setUVRect(0, 0, 1, 1)
	enemy:addImage(gfxQuadMageIdle)
	enemy:addImageName("mage_idle.png")
  
	prop = MOAIProp2D.new()
	prop:setDeck(gfxQuadMageIdle)

	-- Pain image
	gfxQuadMagePain = MOAIGfxQuad2D.new()
	gfxQuadMagePain:setTexture("mage_pain.png")
	gfxQuadMagePain:setRect(-38, -45, 38, 45)
	gfxQuadMagePain:setUVRect(0, 0, 1, 1)
	enemy:addImage(gfxQuadMagePain)
	enemy:addImageName("mage_pain.png")

	-- Die image
	gfxQuadMageDie = MOAIGfxQuad2D.new()
	gfxQuadMageDie:setTexture("mage_die.png")
	gfxQuadMageDie:setRect(-38, -45, 38, 45)
	gfxQuadMageDie:setUVRect(0, 0, 1, 1)
	enemy:addImage(gfxQuadMageDie)
	enemy:addImageName("mage_die.png")

	enemy:setProp(prop, layer)
	enemy:start()
    enemy:setLoc(mouseX, mouseY)
	enemy:setHealth(60)
	enemy:readAndInitializeBehaviorTree("enemybehaviortree.xml")

	player:addTarget(enemy:getPointerToThis())
  end
end

function onRightClick(down)
  if down == true then
  end
end

function pointerCallback(x, y)
    mouseX, mouseY = layer:wndToWorld(x, y)
end

MOAIInputMgr.device.mouseLeft:setCallback(onClick)
MOAIInputMgr.device.mouseRight:setCallback(onRightClick)
MOAIInputMgr.device.pointer:setCallback(pointerCallback)

function onKeyPressed(key, down)
	if key == 32 then
		if down then
			print(tostring(key))
		else
			pathfinder:pathfindStep()
		end
	end
end

if (MOAIInputMgr.device.keyboard) then
    MOAIInputMgr.device.keyboard:setCallback(onKeyPressed)
end

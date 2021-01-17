sprite = nil
speed = 4

function Init()
	-- player:set_str("skin", "https://upload.wikimedia.org/wikipedia/commons/4/47/PNG_transparency_demonstration_1.png")
	-- sprite = ctx.image(player:get_str("skin"))

	sprite = ctx.image("https://f4.bcbits.com/img/a0118737312_10.jpg")

end

function Update()
	if player:is_pressed("D") then
		player.velocity.x = player.velocity.x+speed
	end

	if player:is_pressed("A") then
		player.velocity.x = player.velocity.x-speed
	end

	if player:is_pressed("S") then
		player.velocity.y = player.velocity.y+speed
	end

	if player:is_pressed("W") then
		player.velocity.y = player.velocity.y-speed
	end

	player.position = player.position+player.velocity
	player.velocity = player.velocity:div(1.2)

end

function Draw()
	-- ctx.drawColor(255, 50, 255)
	ctx.draw_image(sprite, player.position.x, player.position.y, 1.0, 1.0, 0.0)
end

function Destroy()
	
end
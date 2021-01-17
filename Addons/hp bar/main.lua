info.name = "Hp Bar"

sprite = nil

function Init()
	-- player:set_str("skin", "https://upload.wikimedia.org/wikipedia/commons/4/47/PNG_transparency_demonstration_1.png")
	-- sprite = ctx.image(player:get_str("skin"))
	print("hi")
	player:set_num("hp", 100);

	sprite = ctx.image("https://www.colorpsychology.org/wp-content/uploads/2015/02/red-color-1.jpg")

end

function Update()

end

function Draw()
	-- ctx.drawColor(255, 50, 255)
	ctx.draw_image(sprite, player.position.x, player.position.y-1.0,  player:get_num("hp")/100.0, 0.1, 0.0)
end

function Destroy()
	
end
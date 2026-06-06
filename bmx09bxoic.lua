local uniqueFeature = ui.checkbox("ragebot", "anti-aim", "movement", "Unique feature$$$")
local bestSliderFeature = ui.slider("ragebot", "anti-aim", "movement", "Slider Feature$$$", 0, 100)

-- boolean
print(uniqueFeature:get())

uniqueFeature:set(true)

print(uniqueFeature:get())

uniqueFeature:setVisible(false)
uniqueFeature:setVisible(true)

-- slider
print(bestSliderFeature:get())
bestSliderFeature:set(99)
print(bestSliderFeature:get())
bestSliderFeature:set(-2309840938)
print(bestSliderFeature:get())
bestSliderFeature:set(50)
print(bestSliderFeature:get())
bestSliderFeature:setVisible(false)
bestSliderFeature:setVisible(true)
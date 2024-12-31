extends Node

func _process(delta: float) -> void:
	if Input.is_action_just_pressed(&"left_click"):
		var bible := FileAccess.get_file_as_bytes("res://text")
		var a     := FileAccess.open("res://compressed", FileAccess.WRITE)
		a.store_buffer(MoreCompression.compress(bible, MoreCompression.COMPRESSION_LZ4))
		a.close()

	if Input.is_action_just_pressed(&"right_click"):
		var a     := FileAccess.get_file_as_bytes("res://compressed")
		var buff  := MoreCompression.decompress(a, 5000, MoreCompression.COMPRESSION_LZ4)
		var bible := buff.get_string_from_ascii()
		print(bible)

module fish_audio_tts

go 1.20

replace nyra_framework => ../../system/nyra_runtime_go/interface

require (
	github.com/vmihailenco/msgpack/v5 v5.4.1
	nyra_framework v0.0.0-00010101000000-000000000000
)

require github.com/vmihailenco/tagparser/v2 v2.0.0 // indirect

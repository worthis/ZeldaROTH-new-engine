CXX = arm-linux-gnueabihf-g++
CFLAGS = -O2 -Wall
CXXFLAGS = -I/opt/miyoomini-toolchain/arm-linux-gnueabihf/libc/usr/include -ISDL
LDFLAGS = -L/opt/miyoomini-toolchain/arm-linux-gnueabihf/libc/usr/lib -LSDL/libs -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_rotozoom
OBJECTS = src/game/algo/AStar.o src/game/keys/Action.o src/game/content/scene/AnimationInGame.o src/game/content/items/Arrow.o src/engine/audio/AudioConfiguration.o src/config/AudioHelper.o src/engine/audio/AudioManager.o src/game/content/items/Bomb.o src/engine/util/geometry/BoundingBox.o src/game/content/objects/Caisse.o src/game/content/scene/Camera.o src/engine/util/time/Chrono.o src/engine/renderer/CircularTransition.o src/game/content/objects/Coffre.o src/game/content/types/Collisionable.o src/game/menu/options/commands/joystick/CommandsJoystick.o src/game/menu/options/commands/joystick/CommandsJoystickController.o src/game/menu/options/commands/keyboard/CommandsKeyboard.o src/game/menu/options/commands/keyboard/CommandsKeyboardController.o src/game/menu/options/commands/main/CommandsMain.o src/game/menu/options/commands/main/CommandsMainController.o src/config/ConfigurationManager.o src/game/ending/credits/Credits.o src/game/ending/credits/CreditsController.o src/game/content/items/Cristal.o src/game/content/effects/Debris.o src/game/content/types/Drawable.o src/game/content/types/Effect.o src/game/ending/EndingController.o src/game/content/types/Ennemi.o src/game/content/ennemis/Ennemi001.o src/game/content/ennemis/Ennemi002.o src/game/content/ennemis/Ennemi003.o src/game/content/ennemis/Ennemi004.o src/game/content/ennemis/Ennemi005.o src/game/content/ennemis/Ennemi006.o src/game/content/ennemis/Ennemi008.o src/game/content/ennemis/Ennemi009.o src/game/content/ennemis/Ennemi010.o src/game/content/ennemis/Ennemi011.o src/game/content/ennemis/Ennemi012.o src/game/content/ennemis/Ennemi013.o src/game/content/ennemis/Ennemi014.o src/game/content/ennemis/Ennemi015.o src/game/content/ennemis/Ennemi016.o src/game/content/ennemis/Ennemi018.o src/game/content/ennemis/Ennemi019.o src/game/content/ennemis/Ennemi021.o src/game/content/ennemis/Ennemi022.o src/game/content/ennemis/Ennemi023.o src/game/content/ennemis/Ennemi024.o src/game/content/ennemis/Ennemi025.o src/game/content/ennemis/Ennemi026.o src/game/content/ennemis/Ennemi027.o src/game/content/ennemis/Ennemi028.o src/game/content/ennemis/Ennemi029.o src/game/content/ennemis/Ennemi030.o src/game/content/ennemis/Ennemi031.o src/game/content/ennemis/Ennemi032.o src/game/content/ennemis/Ennemi033.o src/game/content/ennemis/Ennemi034.o src/game/content/ennemis/Ennemi035.o src/game/content/ennemis/Ennemi037.o src/game/content/ennemis/Ennemi038.o src/game/content/ennemis/Ennemi039.o src/game/content/ennemis/Ennemi040.o src/game/content/ennemis/Ennemi041.o src/game/content/ennemis/Ennemi042.o src/game/content/ennemis/Ennemi043.o src/game/content/ennemis/Ennemi044.o src/game/content/ennemis/Ennemi045.o src/game/content/ennemis/Ennemi046.o src/game/content/ennemis/Ennemi047.o src/game/content/ennemis/Ennemi048.o src/game/content/ennemis/Ennemi050.o src/game/content/ennemis/Ennemi052.o src/game/content/ennemis/Ennemi053.o src/engine/window/Event.o src/game/content/effects/Feuilles.o src/game/ending/final/Final.o src/game/ending/final/FinalController.o src/game/content/effects/Flamme.o src/game/content/effects/FumeeBlanche.o src/game/content/effects/FumeeRose.o src/game/game/GameController.o src/game/game/menu/GameMenuController.o src/game/GlobalSave.o src/game/content/items/GrandeEpee.o src/game/game/help/Help.o src/game/game/help/HelpController.o src/game/content/scene/Hud.o src/game/content/objects/Interrupteur.o src/game/content/link/Inventory.o src/game/content/types/Item.o src/game/content/helper/ItemHelper.o src/game/content/helper/ItemRandomizer.o src/game/content/objects/Jarre.o src/game/keys/JoystickBinder.o src/game/keys/KeyBinder.o src/game/content/link/Link.o src/engine/util/list/List.o src/engine/util/list/ListCell.o src/engine/util/list/Listable.o src/game/logo/Logo.o src/game/logo/LogoController.o src/game/content/types/Loopable.o src/game/content/items/MagieGrand.o src/game/content/items/MagiePetit.o src/game/MainController.o src/game/menu/main/MainMenu.o src/game/menu/main/MainMenuController.o src/game/content/scene/Map.o src/game/game/map/MapController.o src/game/game/map/MapDonjon.o src/game/content/helper/MapHelper.o src/game/content/scene/MapInitializer.o src/game/game/map/MapOverworld.o src/game/game/menu/Menu.o src/game/menu/MenuController.o src/engine/util/time/Metronome.o src/game/game/monsters/Monsters.o src/game/game/monsters/MonstersController.o src/engine/util/tree/Node.o src/game/content/objects/ObjBomb.o src/game/content/types/Object.o src/game/opening/Opening.o src/game/opening/OpeningController.o src/game/opening/OpeningTextArea.o src/game/menu/options/audio/OptionsAudio.o src/game/menu/options/audio/OptionsAudioController.o src/game/menu/options/commands/OptionsCommandsController.o src/game/menu/options/OptionsController.o src/game/menu/options/game/OptionsGame.o src/game/menu/options/game/OptionsGameController.o src/game/menu/options/main/OptionsMain.o src/game/menu/options/main/OptionsMainController.o src/game/content/objects/Pancarte.o src/game/content/items/PetitCoeur.o src/game/content/items/PetiteCle.o src/game/content/items/PetiteEpee.o src/game/content/objects/PiegeDemi.o src/game/content/objects/PiegeFeu.o src/game/content/objects/PiegeMain.o src/game/content/objects/PiegePics.o src/game/content/objects/Pierre.o src/game/content/effects/Plouf.o src/game/content/objects/Pnj.o src/game/content/types/Portable.o src/game/content/objects/Poule.o src/game/content/types/Poussable.o src/game/content/projectiles/ProjArcMagique.o src/game/content/projectiles/ProjArrow.o src/game/content/projectiles/ProjBaguetteFeu.o src/game/content/projectiles/ProjBaguetteGlace.o src/game/content/projectiles/ProjBigFeu.o src/game/content/projectiles/ProjBigGlace.o src/game/content/projectiles/ProjBouleDemi.o src/game/content/projectiles/ProjBouleFeu.o src/game/content/projectiles/ProjBoulet.o src/game/content/projectiles/ProjEclair.o src/game/content/projectiles/ProjFeuLong.o src/game/content/projectiles/ProjGrappin.o src/game/content/projectiles/ProjLapin.o src/game/content/projectiles/ProjUltime.o src/game/content/types/Projectile.o src/game/content/helper/ProjectileHelper.o src/engine/util/tree/Quadtree.o src/game/content/items/QuartCoeur.o src/game/menu/records/Records.o src/game/menu/records/RecordsController.o src/engine/resources/ResourceManager.o src/game/content/items/RubisBleu.o src/game/content/items/RubisRouge.o src/game/content/items/RubisVert.o src/game/Save.o src/game/game/scene/Scene.o src/game/game/scene/SceneController.o src/game/ending/score/Score.o src/game/ending/score/ScoreController.o src/game/content/link/Shield.o src/engine/renderer/SimpleTransition.o src/engine/util/physic/SlideManager.o src/game/content/objects/Sphere.o src/game/content/link/Status.o src/game/ending/story/StoryController.o src/game/ending/story/StoryTextArea.o src/game/content/link/Sword.o src/game/content/objects/TalkableArea.o src/game/game/teleport/Teleport.o src/game/game/teleport/TeleportController.o src/engine/texts/Text.o src/game/game/textes/TextArea.o src/engine/texts/TextConfiguration.o src/game/game/textes/TextController.o src/config/TextHelper.o src/engine/texts/TextManager.o src/engine/window/Timer.o src/game/title/Title.o src/game/title/TitleController.o src/game/game/transitionMaps/TransitionMaps.o src/game/game/transitionMaps/TransitionMapsController.o src/game/game/transitionRooms/TransitionRooms.o src/game/game/transitionRooms/TransitionRoomsController.o src/game/content/items/Triforce.o src/engine/resources/WFile.o src/engine/resources/WImage.o src/engine/resources/WMusic.o src/engine/resources/WResource.o src/engine/resources/WSound.o src/engine/window/WindowManager.o src/main.o 
OUTPUT = Zelda


main: $(OBJECTS)
	$(CXX) $(OBJECTS) $(CFLAGS) -o $(OUTPUT) $(LDFLAGS)
AStar.o: AStar.cpp
	$(CXX) $(CFLAGS) -c AStar.cpp
Action.o:
	$(CXX) $(CFLAGS) -c Action.cpp
AnimationInGame.o:
	$(CXX) $(CFLAGS) -c AnimationInGame.cpp
Arrow.o:
	$(CXX) $(CFLAGS) -c Arrow.cpp
AudioConfiguration.o:
	$(CXX) $(CFLAGS) -c AudioConfiguration.cpp
AudioHelper.o:
	$(CXX) $(CFLAGS) -c AudioHelper.cpp
AudioManager.o:
	$(CXX) $(CFLAGS) -c AudioManager.cpp
Bomb.o:
	$(CXX) $(CFLAGS) -c Bomb.cpp
BoundingBox.o:
	$(CXX) $(CFLAGS) -c BoundingBox.cpp
Caisse.o:
	$(CXX) $(CFLAGS) -c Caisse.cpp
Camera.o:
	$(CXX) $(CFLAGS) -c Camera.cpp
Chrono.o:
	$(CXX) $(CFLAGS) -c Chrono.cpp
CircularTransition.o:
	$(CXX) $(CFLAGS) -c CircularTransition.cpp
Coffre.o:
	$(CXX) $(CFLAGS) -c Coffre.cpp
Collisionable.o:
	$(CXX) $(CFLAGS) -c Collisionable.cpp
CommandsJoystick.o:
	$(CXX) $(CFLAGS) -c CommandsJoystick.cpp
CommandsJoystickController.o:
	$(CXX) $(CFLAGS) -c CommandsJoystickController.cpp
CommandsKeyboard.o:
	$(CXX) $(CFLAGS) -c CommandsKeyboard.cpp
CommandsKeyboardController.o:
	$(CXX) $(CFLAGS) -c CommandsKeyboardController.cpp
CommandsMain.o:
	$(CXX) $(CFLAGS) -c CommandsMain.cpp
CommandsMainController.o:
	$(CXX) $(CFLAGS) -c CommandsMainController.cpp
ConfigurationManager.o:
	$(CXX) $(CFLAGS) -c ConfigurationManager.cpp
Credits.o:
	$(CXX) $(CFLAGS) -c Credits.cpp
CreditsController.o:
	$(CXX) $(CFLAGS) -c CreditsController.cpp
Cristal.o:
	$(CXX) $(CFLAGS) -c Cristal.cpp
Debris.o:
	$(CXX) $(CFLAGS) -c Debris.cpp
Drawable.o:
	$(CXX) $(CFLAGS) -c Drawable.cpp
Effect.o:
	$(CXX) $(CFLAGS) -c Effect.cpp
EndingController.o:
	$(CXX) $(CFLAGS) -c EndingController.cpp
Ennemi.o:
	$(CXX) $(CFLAGS) -c Ennemi.cpp
Ennemi001.o:
	$(CXX) $(CFLAGS) -c Ennemi001.cpp
Ennemi002.o:
	$(CXX) $(CFLAGS) -c Ennemi002.cpp
Ennemi003.o:
	$(CXX) $(CFLAGS) -c Ennemi003.cpp
Ennemi004.o:
	$(CXX) $(CFLAGS) -c Ennemi004.cpp
Ennemi005.o:
	$(CXX) $(CFLAGS) -c Ennemi005.cpp
Ennemi006.o:
	$(CXX) $(CFLAGS) -c Ennemi006.cpp
Ennemi008.o:
	$(CXX) $(CFLAGS) -c Ennemi008.cpp
Ennemi009.o:
	$(CXX) $(CFLAGS) -c Ennemi009.cpp
Ennemi010.o:
	$(CXX) $(CFLAGS) -c Ennemi010.cpp
Ennemi011.o:
	$(CXX) $(CFLAGS) -c Ennemi011.cpp
Ennemi012.o:
	$(CXX) $(CFLAGS) -c Ennemi012.cpp
Ennemi013.o:
	$(CXX) $(CFLAGS) -c Ennemi013.cpp
Ennemi014.o:
	$(CXX) $(CFLAGS) -c Ennemi014.cpp
Ennemi015.o:
	$(CXX) $(CFLAGS) -c Ennemi015.cpp
Ennemi016.o:
	$(CXX) $(CFLAGS) -c Ennemi016.cpp
Ennemi018.o:
	$(CXX) $(CFLAGS) -c Ennemi018.cpp
Ennemi019.o:
	$(CXX) $(CFLAGS) -c Ennemi019.cpp
Ennemi021.o:
	$(CXX) $(CFLAGS) -c Ennemi021.cpp
Ennemi022.o:
	$(CXX) $(CFLAGS) -c Ennemi022.cpp
Ennemi023.o:
	$(CXX) $(CFLAGS) -c Ennemi023.cpp
Ennemi024.o:
	$(CXX) $(CFLAGS) -c Ennemi024.cpp
Ennemi025.o:
	$(CXX) $(CFLAGS) -c Ennemi025.cpp
Ennemi026.o:
	$(CXX) $(CFLAGS) -c Ennemi026.cpp
Ennemi027.o:
	$(CXX) $(CFLAGS) -c Ennemi027.cpp
Ennemi028.o:
	$(CXX) $(CFLAGS) -c Ennemi028.cpp
Ennemi029.o:
	$(CXX) $(CFLAGS) -c Ennemi029.cpp
Ennemi030.o:
	$(CXX) $(CFLAGS) -c Ennemi030.cpp
Ennemi031.o:
	$(CXX) $(CFLAGS) -c Ennemi031.cpp
Ennemi032.o:
	$(CXX) $(CFLAGS) -c Ennemi032.cpp
Ennemi033.o:
	$(CXX) $(CFLAGS) -c Ennemi033.cpp
Ennemi034.o:
	$(CXX) $(CFLAGS) -c Ennemi034.cpp
Ennemi035.o:
	$(CXX) $(CFLAGS) -c Ennemi035.cpp
Ennemi037.o:
	$(CXX) $(CFLAGS) -c Ennemi037.cpp
Ennemi038.o:
	$(CXX) $(CFLAGS) -c Ennemi038.cpp
Ennemi039.o:
	$(CXX) $(CFLAGS) -c Ennemi039.cpp
Ennemi040.o:
	$(CXX) $(CFLAGS) -c Ennemi040.cpp
Ennemi041.o:
	$(CXX) $(CFLAGS) -c Ennemi041.cpp
Ennemi042.o:
	$(CXX) $(CFLAGS) -c Ennemi042.cpp
Ennemi043.o:
	$(CXX) $(CFLAGS) -c Ennemi043.cpp
Ennemi044.o:
	$(CXX) $(CFLAGS) -c Ennemi044.cpp
Ennemi045.o:
	$(CXX) $(CFLAGS) -c Ennemi045.cpp
Ennemi046.o:
	$(CXX) $(CFLAGS) -c Ennemi046.cpp
Ennemi047.o:
	$(CXX) $(CFLAGS) -c Ennemi047.cpp
Ennemi048.o:
	$(CXX) $(CFLAGS) -c Ennemi048.cpp
Ennemi050.o:
	$(CXX) $(CFLAGS) -c Ennemi050.cpp
Ennemi052.o:
	$(CXX) $(CFLAGS) -c Ennemi052.cpp
Ennemi053.o:
	$(CXX) $(CFLAGS) -c Ennemi053.cpp
Event.o:
	$(CXX) $(CFLAGS) -c Event.cpp
Feuilles.o:
	$(CXX) $(CFLAGS) -c Feuilles.cpp
Final.o:
	$(CXX) $(CFLAGS) -c Final.cpp
FinalController.o:
	$(CXX) $(CFLAGS) -c FinalController.cpp
Flamme.o:
	$(CXX) $(CFLAGS) -c Flamme.cpp
FumeeBlanche.o:
	$(CXX) $(CFLAGS) -c FumeeBlanche.cpp
FumeeRose.o:
	$(CXX) $(CFLAGS) -c FumeeRose.cpp
GameController.o:
	$(CXX) $(CFLAGS) -c GameController.cpp
GameMenuController.o:
	$(CXX) $(CFLAGS) -c GameMenuController.cpp
GlobalSave.o:
	$(CXX) $(CFLAGS) -c GlobalSave.cpp
GrandeEpee.o:
	$(CXX) $(CFLAGS) -c GrandeEpee.cpp
Help.o:
	$(CXX) $(CFLAGS) -c Help.cpp
HelpController.o:
	$(CXX) $(CFLAGS) -c HelpController.cpp
Hud.o:
	$(CXX) $(CFLAGS) -c Hud.cpp
Interrupteur.o:
	$(CXX) $(CFLAGS) -c Interrupteur.cpp
Inventory.o:
	$(CXX) $(CFLAGS) -c Inventory.cpp
Item.o:
	$(CXX) $(CFLAGS) -c Item.cpp
ItemHelper.o:
	$(CXX) $(CFLAGS) -c ItemHelper.cpp
ItemRandomizer.o:
	$(CXX) $(CFLAGS) -c ItemRandomizer.cpp
Jarre.o:
	$(CXX) $(CFLAGS) -c Jarre.cpp
JoystickBinder.o:
	$(CXX) $(CFLAGS) -c JoystickBinder.cpp
KeyBinder.o:
	$(CXX) $(CFLAGS) -c KeyBinder.cpp
Link.o:
	$(CXX) $(CFLAGS) -c Link.cpp
List.o:
	$(CXX) $(CFLAGS) -c List.cpp
ListCell.o:
	$(CXX) $(CFLAGS) -c ListCell.cpp
Listable.o:
	$(CXX) $(CFLAGS) -c Listable.cpp
Logo.o:
	$(CXX) $(CFLAGS) -c Logo.cpp
LogoController.o:
	$(CXX) $(CFLAGS) -c LogoController.cpp
Loopable.o:
	$(CXX) $(CFLAGS) -c Loopable.cpp
MagieGrand.o:
	$(CXX) $(CFLAGS) -c MagieGrand.cpp
MagiePetit.o:
	$(CXX) $(CFLAGS) -c MagiePetit.cpp
MainController.o:
	$(CXX) $(CFLAGS) -c MainController.cpp
MainMenu.o:
	$(CXX) $(CFLAGS) -c MainMenu.cpp
MainMenuController.o:
	$(CXX) $(CFLAGS) -c MainMenuController.cpp
Map.o:
	$(CXX) $(CFLAGS) -c Map.cpp
MapController.o:
	$(CXX) $(CFLAGS) -c MapController.cpp
MapDonjon.o:
	$(CXX) $(CFLAGS) -c MapDonjon.cpp
MapHelper.o:
	$(CXX) $(CFLAGS) -c MapHelper.cpp
MapInitializer.o:
	$(CXX) $(CFLAGS) -c MapInitializer.cpp
MapOverworld.o:
	$(CXX) $(CFLAGS) -c MapOverworld.cpp
Menu.o:
	$(CXX) $(CFLAGS) -c Menu.cpp
MenuController.o:
	$(CXX) $(CFLAGS) -c MenuController.cpp
Metronome.o:
	$(CXX) $(CFLAGS) -c Metronome.cpp
Monsters.o:
	$(CXX) $(CFLAGS) -c Monsters.cpp
MonstersController.o:
	$(CXX) $(CFLAGS) -c MonstersController.cpp
Node.o:
	$(CXX) $(CFLAGS) -c Node.cpp
ObjBomb.o:
	$(CXX) $(CFLAGS) -c ObjBomb.cpp
Object.o:
	$(CXX) $(CFLAGS) -c Object.cpp
Opening.o:
	$(CXX) $(CFLAGS) -c Opening.cpp
OpeningController.o:
	$(CXX) $(CFLAGS) -c OpeningController.cpp
OpeningTextArea.o:
	$(CXX) $(CFLAGS) -c OpeningTextArea.cpp
OptionsAudio.o:
	$(CXX) $(CFLAGS) -c OptionsAudio.cpp
OptionsAudioController.o:
	$(CXX) $(CFLAGS) -c OptionsAudioController.cpp
OptionsCommandsController.o:
	$(CXX) $(CFLAGS) -c OptionsCommandsController.cpp
OptionsController.o:
	$(CXX) $(CFLAGS) -c OptionsController.cpp
OptionsGame.o:
	$(CXX) $(CFLAGS) -c OptionsGame.cpp
OptionsGameController.o:
	$(CXX) $(CFLAGS) -c OptionsGameController.cpp
OptionsMain.o:
	$(CXX) $(CFLAGS) -c OptionsMain.cpp
OptionsMainController.o:
	$(CXX) $(CFLAGS) -c OptionsMainController.cpp
Pancarte.o:
	$(CXX) $(CFLAGS) -c Pancarte.cpp
PetitCoeur.o:
	$(CXX) $(CFLAGS) -c PetitCoeur.cpp
PetiteCle.o:
	$(CXX) $(CFLAGS) -c PetiteCle.cpp
PetiteEpee.o:
	$(CXX) $(CFLAGS) -c PetiteEpee.cpp
PiegeDemi.o:
	$(CXX) $(CFLAGS) -c PiegeDemi.cpp
PiegeFeu.o:
	$(CXX) $(CFLAGS) -c PiegeFeu.cpp
PiegeMain.o:
	$(CXX) $(CFLAGS) -c PiegeMain.cpp
PiegePics.o:
	$(CXX) $(CFLAGS) -c PiegePics.cpp
Pierre.o:
	$(CXX) $(CFLAGS) -c Pierre.cpp
Plouf.o:
	$(CXX) $(CFLAGS) -c Plouf.cpp
Pnj.o:
	$(CXX) $(CFLAGS) -c Pnj.cpp
Portable.o:
	$(CXX) $(CFLAGS) -c Portable.cpp
Poule.o:
	$(CXX) $(CFLAGS) -c Poule.cpp
Poussable.o:
	$(CXX) $(CFLAGS) -c Poussable.cpp
ProjArcMagique.o:
	$(CXX) $(CFLAGS) -c ProjArcMagique.cpp
ProjArrow.o:
	$(CXX) $(CFLAGS) -c ProjArrow.cpp
ProjBaguetteFeu.o:
	$(CXX) $(CFLAGS) -c ProjBaguetteFeu.cpp
ProjBaguetteGlace.o:
	$(CXX) $(CFLAGS) -c ProjBaguetteGlace.cpp
ProjBigFeu.o:
	$(CXX) $(CFLAGS) -c ProjBigFeu.cpp
ProjBigGlace.o:
	$(CXX) $(CFLAGS) -c ProjBigGlace.cpp
ProjBouleDemi.o:
	$(CXX) $(CFLAGS) -c ProjBouleDemi.cpp
ProjBouleFeu.o:
	$(CXX) $(CFLAGS) -c ProjBouleFeu.cpp
ProjBoulet.o:
	$(CXX) $(CFLAGS) -c ProjBoulet.cpp
ProjEclair.o:
	$(CXX) $(CFLAGS) -c ProjEclair.cpp
ProjFeuLong.o:
	$(CXX) $(CFLAGS) -c ProjFeuLong.cpp
ProjGrappin.o:
	$(CXX) $(CFLAGS) -c ProjGrappin.cpp
ProjLapin.o:
	$(CXX) $(CFLAGS) -c ProjLapin.cpp
ProjUltime.o:
	$(CXX) $(CFLAGS) -c ProjUltime.cpp
Projectile.o:
	$(CXX) $(CFLAGS) -c Projectile.cpp
ProjectileHelper.o:
	$(CXX) $(CFLAGS) -c ProjectileHelper.cpp
Quadtree.o:
	$(CXX) $(CFLAGS) -c Quadtree.cpp
QuartCoeur.o:
	$(CXX) $(CFLAGS) -c QuartCoeur.cpp
Records.o:
	$(CXX) $(CFLAGS) -c Records.cpp
RecordsController.o:
	$(CXX) $(CFLAGS) -c RecordsController.cpp
ResourceManager.o:
	$(CXX) $(CFLAGS) -c ResourceManager.cpp
RubisBleu.o:
	$(CXX) $(CFLAGS) -c RubisBleu.cpp
RubisRouge.o:
	$(CXX) $(CFLAGS) -c RubisRouge.cpp
RubisVert.o:
	$(CXX) $(CFLAGS) -c RubisVert.cpp
Save.o:
	$(CXX) $(CFLAGS) -c Save.cpp
Scene.o:
	$(CXX) $(CFLAGS) -c Scene.cpp
SceneController.o:
	$(CXX) $(CFLAGS) -c SceneController.cpp
Score.o:
	$(CXX) $(CFLAGS) -c Score.cpp
ScoreController.o:
	$(CXX) $(CFLAGS) -c ScoreController.cpp
Shield.o:
	$(CXX) $(CFLAGS) -c Shield.cpp
SimpleTransition.o:
	$(CXX) $(CFLAGS) -c SimpleTransition.cpp
SlideManager.o:
	$(CXX) $(CFLAGS) -c SlideManager.cpp
Sphere.o:
	$(CXX) $(CFLAGS) -c Sphere.cpp
Status.o:
	$(CXX) $(CFLAGS) -c Status.cpp
StoryController.o:
	$(CXX) $(CFLAGS) -c StoryController.cpp
StoryTextArea.o:
	$(CXX) $(CFLAGS) -c StoryTextArea.cpp
Sword.o:
	$(CXX) $(CFLAGS) -c Sword.cpp
TalkableArea.o:
	$(CXX) $(CFLAGS) -c TalkableArea.cpp
Teleport.o:
	$(CXX) $(CFLAGS) -c Teleport.cpp
TeleportController.o:
	$(CXX) $(CFLAGS) -c TeleportController.cpp
Text.o:
	$(CXX) $(CFLAGS) -c Text.cpp
TextArea.o:
	$(CXX) $(CFLAGS) -c TextArea.cpp
TextConfiguration.o:
	$(CXX) $(CFLAGS) -c TextConfiguration.cpp
TextController.o:
	$(CXX) $(CFLAGS) -c TextController.cpp
TextHelper.o:
	$(CXX) $(CFLAGS) -c TextHelper.cpp
TextManager.o:
	$(CXX) $(CFLAGS) -c TextManager.cpp
Timer.o:
	$(CXX) $(CFLAGS) -c Timer.cpp
Title.o:
	$(CXX) $(CFLAGS) -c Title.cpp
TitleController.o:
	$(CXX) $(CFLAGS) -c TitleController.cpp
TransitionMaps.o:
	$(CXX) $(CFLAGS) -c TransitionMaps.cpp
TransitionMapsController.o:
	$(CXX) $(CFLAGS) -c TransitionMapsController.cpp
TransitionRooms.o:
	$(CXX) $(CFLAGS) -c TransitionRooms.cpp
TransitionRoomsController.o:
	$(CXX) $(CFLAGS) -c TransitionRoomsController.cpp
Triforce.o:
	$(CXX) $(CFLAGS) -c Triforce.cpp
WFile.o:
	$(CXX) $(CFLAGS) -c WFile.cpp
WImage.o:
	$(CXX) $(CFLAGS) -c WImage.cpp
WMusic.o:
	$(CXX) $(CFLAGS) -c WMusic.cpp
WResource.o:
	$(CXX) $(CFLAGS) -c WResource.cpp
WSound.o:
	$(CXX) $(CFLAGS) -c WSound.cpp
WindowManager.o:
	$(CXX) $(CFLAGS) -c WindowManager.cpp
main.o:
	$(CXX) $(CFLAGS) -c main.cpp

.PHONY : clean

clean :
	-rm -f $(OBJECTS) $(OUTPUT)
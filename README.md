# MxO Engine
A simple c++ engine for loading the MXO assets

# How to run
Clone the solution, extract the Deps archive, open MxoClient.sln go into CppGame.cpp and change:

CppGame::Loader.initialize("G:/Matrix Online");

To your game path

you can change what file it tries to load in 

CppGame::Loader.get_file(0x28000DB1, &meshDataSize, meshData)

the first number is the hex id of the model
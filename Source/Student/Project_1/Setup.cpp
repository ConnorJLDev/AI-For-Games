#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
    // Create an agent (using the default "Agent::AgentModel::Man" model)
    //auto man = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::Example);

    // You can change properties here or at runtime from a behavior tree leaf node
    // Look in Agent.h for all of the setters, like these:
    // man->set_color(Vec3(1, 0, 1));
    // man->set_scaling(Vec3(7,7,7));
    // man->set_position(Vec3(100, 0, 100));

    // Create an agent with a different 3D model:
    // 1. (optional) Add a new 3D model to the framework other than the ones provided:
    //    A. Find a ".sdkmesh" model or use https://github.com/walbourn/contentexporter
    //       to convert fbx files (many end up corrupted in this process, so good luck!)
    //    B. Add a new AgentModel enum for your model in Agent.h (like the existing Man or Tree).
    // 2. Register the new model with the engine, so it associates the file path with the enum
    //    A. Here we are registering all of the extra models that already come in the package.
    Agent::add_model("Assets\\tree.sdkmesh", Agent::AgentModel::Tree);
    Agent::add_model("Assets\\car.sdkmesh", Agent::AgentModel::Car);
    Agent::add_model("Assets\\bird.sdkmesh", Agent::AgentModel::Bird);
    Agent::add_model("Assets\\ball.sdkmesh", Agent::AgentModel::Ball);
    Agent::add_model("Assets\\hut.sdkmesh", Agent::AgentModel::Hut);
    // 3. Create the agent, giving it the correct AgentModel type.
   // auto tree = agents->create_behavior_agent("ExampleAgent2", BehaviorTreeTypes::Example, Agent::AgentModel::Tree);
    // 4. (optional) You can also set the pitch of the model, if you want it to be rotated differently
   // tree->set_pitch(PI / 2);
    // 5. (optional) Set other aspects to make it start out correctly
   // tree->set_color(Vec3(0, 0.5, 0));   // Set the tree to green


    auto Baron = agents->create_behavior_agent("Baron", BehaviorTreeTypes::Baron, Agent::AgentModel::Man);
    Baron->set_position(Vec3(50.0, 0.0, 0.0));
    Baron->set_color(Vec3(0, 0.5, 0));


    auto Singer = agents->create_behavior_agent("Singer", BehaviorTreeTypes::Singer, Agent::AgentModel::Man);
    Singer->set_yaw(Singer->get_yaw() + PI);
    Singer->set_position(Vec3(50.0, 0.0, 100.0));
    Singer->set_color(Vec3(0, 0.0, 0.5));



    auto Dancer = agents->create_behavior_agent("Dancer", BehaviorTreeTypes::Dancer, Agent::AgentModel::Man);
    Dancer->set_yaw(Singer->get_yaw() - PI/2);
    Dancer->set_position(Vec3(00.0, 0.0, 50.0));
    Dancer->set_color(Vec3(0.5, 0, 0));


    auto Lover = agents->create_behavior_agent("Lover", BehaviorTreeTypes::Lover, Agent::AgentModel::Man);
    Lover->set_position(Vec3(50.0, 0.0, 50.0));
    Lover->set_color(Vec3(0.5, 0.5, 0.5));

    auto& bb = Lover->get_blackboard();
    bb.set_value("LoverInit", false);
    {
        auto& bb = Singer->get_blackboard();
    
        bb.set_value<bool>("Singer Performing", false);
    }
    {
        auto& bb = Baron->get_blackboard();
        bb.set_value<bool>("Baron Performing", false);
    }
    {
        auto& bb = Dancer->get_blackboard();
        bb.set_value<bool>("Dancer Performing", false);
    }

    // You can technically load any map you want, even create your own map file,
    // but behavior agents won't actually avoid walls or anything special, unless you code
    // that yourself (that's the realm of project 2)
    terrain->goto_map(0);

    // You can also enable the pathing layer and set grid square colors as you see fit.
    // Works best with map 0, the completely blank map
    terrain->pathLayer.set_enabled(true);
    terrain->pathLayer.set_value(0, 0, Colors::Red);

    // Camera position can be modified from this default
    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(-62.0f, 70.0f, terrain->mapSizeInWorld * 0.5f));
    camera->set_pitch(0.610865); // 35 degrees

    // Sound control (these sound functions can be kicked off in a behavior tree node - see the example in L_PlaySound.cpp)
    //audioManager->SetVolume(0.5f);
    //audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");


    // Uncomment for example on playing music in the engine (must be .wav)
    // audioManager->PlayMusic(L"Assets\\Audio\\motivate.wav");
    // audioManager->PauseMusic(...);
    // audioManager->ResumeMusic(...);
    // audioManager->StopMusic(...);
}
#include <qbo_talk/Text2Speach.h>
#include <qbo_listen/Listened.h>
 
ros::ServiceClient client_talker;
qbo_talk::Text2Speach srv_talker;
 
void speak_this(std::string to_speak)
{
    srv_talker.request.command = to_speak;
 
    if (client_talker.call(srv_talker))
        ROS_INFO("Spoken: %s", to_speak.c_str());
    else
        ROS_ERROR("Failed to call the service of qbo_talk");
}
 
void listenerCallback(const qbo_listen::ListenedConstPtr& msg)
{
    std::string listened = msg->msg;
    ROS_INFO("Listened: %s",listened.c_str());
 
    if(listened == "HELLO QBO")
        speak_this("Hello, human");
    else if(listened == "GOODBYE QBO")
        speak_this("Goodbye human");
 
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "qbo_conversation");
 
    ros::NodeHandle nh; 
 
    client_talker = nh.serviceClient<qbo_talk::Text2Speach>("/qbo_talk/festival_say");
    ros::Subscriber listener_sub =nh.subscribe<qbo_listen::Listened>("/listen/en_questions",1,listenerCallback);
 
    ROS_INFO("qbo_conversation node is launched");
 
    ros::spin();
 
    return 0;
}

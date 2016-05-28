#ifndef _ROS_std_msgs_brazenbot_h
#define _ROS_std_msgs_brazenbot_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace brazen_msgs
{

  class brazenbot : public ros::Msg
  {
    public:
     uint16_t cmd_status;
     uint16_t servo_enable;
     uint16_t servo1a_pos;
     uint16_t servo2a_pos;
     uint16_t servo3a_pos;
     uint16_t servo4a_pos;
     uint16_t servo5a_pos;
     uint16_t servo6a_pos;
     uint16_t servo1b_pos;
     uint16_t servo2b_pos;
     uint16_t servo3b_pos;
     uint16_t servo4b_pos;
     uint16_t servo5b_pos;
     uint16_t servo6b_pos;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;

      *(outbuffer + offset + 0) = (this->cmd_status >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cmd_status >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo_enable);

      *(outbuffer + offset + 0) = (this->servo_enable >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo_enable >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo_enable);

      *(outbuffer + offset + 0) = (this->servo1a_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo1a_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo1a_pos);

      *(outbuffer + offset + 0) = (this->servo2a_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo2a_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo2a_pos);

      *(outbuffer + offset + 0) = (this->servo3a_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo3a_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo3a_pos);

      *(outbuffer + offset + 0) = (this->servo4a_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo4a_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo4a_pos);

      *(outbuffer + offset + 0) = (this->servo5a_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo5a_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo5a_pos);

      *(outbuffer + offset + 0) = (this->servo6a_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo6a_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo6a_pos);
 
      *(outbuffer + offset + 0) = (this->servo1b_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo1b_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo1b_pos);

      *(outbuffer + offset + 0) = (this->servo2b_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo2b_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo2b_pos);

      *(outbuffer + offset + 0) = (this->servo3b_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo3b_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo3b_pos);

      *(outbuffer + offset + 0) = (this->servo4b_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo4b_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo4b_pos);

      *(outbuffer + offset + 0) = (this->servo5b_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo5b_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo5b_pos);

      *(outbuffer + offset + 0) = (this->servo6b_pos >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo6b_pos >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo6b_pos);

      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;

      this->cmd_status =  ((uint16_t) (*(inbuffer + offset)));
      this->cmd_status |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->cmd_status);

      this->servo_enable =  ((uint16_t) (*(inbuffer + offset)));
      this->servo_enable |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo_enable);

      this->servo1a_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo1a_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo1a_pos);

      this->servo2a_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo2a_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo2a_pos);

      this->servo3a_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo3a_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo3a_pos);

      this->servo4a_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo4a_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo4a_pos);

      this->servo5a_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo5a_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo5a_pos);

      this->servo6a_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo6a_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo6a_pos);

      this->servo1b_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo1b_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo1b_pos);

      this->servo2b_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo2b_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo2b_pos);

      this->servo3b_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo3b_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo3b_pos);

      this->servo4b_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo4b_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo4b_pos);

      this->servo5b_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo5b_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo5b_pos);

      this->servo6b_pos =  ((uint16_t) (*(inbuffer + offset)));
      this->servo6b_pos |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo6b_pos);

     return offset;
    }

    const char * getType(){ return "brazen_msgs/brazenbot"; };
    const char * getMD5(){ return "665609039687e823f2130a09fc6bbbd7"; };

  };

}
#endif

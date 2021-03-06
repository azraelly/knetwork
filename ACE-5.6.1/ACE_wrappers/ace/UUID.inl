// -*- C++ -*-
//
//$Id: UUID.inl 74165 2006-08-22 09:38:29Z johnnyw $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace ACE_Utils
{

  /// Data Members for Class Attributes
  ACE_INLINE ACE_UINT32
  UUID::timeLow (void) const
  {
    return this->timeLow_;
  }

  ACE_INLINE void
  UUID::timeLow (ACE_UINT32 timelow)
  {
    this->timeLow_ = timelow;
  }

  ACE_INLINE ACE_UINT16
  UUID::timeMid (void) const
  {
    return this->timeMid_;
  }

  ACE_INLINE void
  UUID::timeMid (ACE_UINT16 time_mid)
  {
    this->timeMid_ = time_mid;
  }

  ACE_INLINE ACE_UINT16
  UUID::timeHiAndVersion (void) const
  {
    return this->timeHiAndVersion_;
  }

  ACE_INLINE void
  UUID::timeHiAndVersion (ACE_UINT16 timeHiAndVersion)
  {
    this->timeHiAndVersion_ = timeHiAndVersion;
  }

  ACE_INLINE u_char
  UUID::clockSeqHiAndReserved (void) const
  {
    return this->clockSeqHiAndReserved_;
  }

  ACE_INLINE void
  UUID::clockSeqHiAndReserved (u_char clockSeqHiAndReserved)
  {
    this->clockSeqHiAndReserved_ = clockSeqHiAndReserved;
  }

  ACE_INLINE u_char
  UUID::clockSeqLow (void) const
  {
    return this->clockSeqLow_;
  }

  ACE_INLINE void
  UUID::clockSeqLow (u_char clockSeqLow)
  {
    this->clockSeqLow_ = clockSeqLow;
  }

  ACE_INLINE UUID_node*
  UUID::node (void) const
  {
    return this->node_;
  }

  ACE_INLINE void
  UUID::node (UUID_node* node)
  {
    if (node_release_)
      delete node_;

    this->node_ = node;
    node_release_ = false;
  }

  ACE_INLINE ACE_CString*
  UUID::thr_id (void)
  {
    return &this->thr_id_;
  }

  ACE_INLINE void
  UUID::thr_id (char* thr_id)
  {
    this->thr_id_ = thr_id;
  }

  ACE_INLINE ACE_CString*
  UUID::pid (void)
  {
    return &this->pid_;
  }

  ACE_INLINE void
  UUID::pid (char* pid)
  {
    this->pid_ = pid;
  }

  ACE_INLINE void
  UUID::from_string (const ACE_CString& uuidString)
  {
    this->from_string_i (uuidString);
  }

  ACE_INLINE bool
  UUID::operator == (const UUID &right) const
  {
    if ((this->timeLow_ != right.timeLow ()) ||
        (this->timeMid_ != right.timeMid ()) ||
        (this->timeHiAndVersion_ != right.timeHiAndVersion ()) ||
        (this->clockSeqHiAndReserved_ != right.clockSeqHiAndReserved ()) ||
        (this->clockSeqLow_ != right.clockSeqLow ()) ||
        (*this->node_ != *right.node ()))
      {
        return false;
      }

      return true;
  }

  ACE_INLINE bool
  UUID::operator != (const UUID &right) const
  {
    return !(*this == right);
  }

//  ACE_INLINE bool
//UUID::operator < (const UUID &rt) const
//  {
//    UUID right (rt);
//    if ((timeLow_ < right.timeLow ()) ||
//        (timeMid_ < right.timeMid ()) ||
//        (timeHiAndVersion_ < right.timeHiAndVersion ()) ||
//        (clockSeqHiAndReserved_ < right.clockSeqHiAndReserved ()) ||
//        (clockSeqLow_ < right.clockSeqLow ()) ||
//        (node_ < right.node ()))
//      {
//        return true;
//      }
//
//    return false;
//  }
//
//  ACE_INLINE bool
//  UUID::operator > (const UUID &right) const
//  {
//    return right < *this;
//  }
//
//  ACE_INLINE bool
//  UUID::operator <= (const UUID &right) const
//  {
//    return !(*this > right);
//  }
//
//  ACE_INLINE bool
//  UUID::operator >= (const UUID &right) const
//  {
//    return !(*this < right);
//  }
//
  ACE_INLINE bool
  UUID_node::operator == (const UUID_node& rt) const
  {
    for (size_t i = 0; i < NODE_ID_SIZE; ++i)
    {
      if (nodeID_ [i] != rt.nodeID_ [i])
        {
          return false;
        }
    }
    return true;
  }

  ACE_INLINE bool
  UUID_node::operator != (const UUID_node& right) const
  {
    return !(*this == right);
  }

//  ACE_INLINE bool
//  UUID_node::operator < (const UUID_node& rt) const
//  {
//    UUID_node right = rt;
//    for (size_t i = 0; i < NODE_ID_SIZE; ++i)
//      if (nodeID_ [i] < right.nodeID ()[i])
//      return true;
//
//    return false;
//  }
}

ACE_END_VERSIONED_NAMESPACE_DECL

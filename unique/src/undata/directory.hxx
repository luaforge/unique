#pragma once
#include"data.hxx"

namespace undata{//tolua_export
  /*
   *  FSTREAM
   */
  class FSTREAM: public STREAM{
  protected:
    pos_type __rpos,__wpos;
    int __fd; // file stream descriptor
    
    virtual void __open();
    virtual void __close();
    virtual void __read (void* chunk, pos_type count);
    virtual void __write(const void* chunk, pos_type count);
    virtual pos_type __tellr()const;
    virtual pos_type __tellw()const;
    virtual void __seekr(pos_type count,DIR dir);
    virtual void __seekw(pos_type count,DIR dir);
  public:
    FSTREAM();
    FSTREAM(REPOS* repos);
    virtual ~FSTREAM();
  };
  /*
   *  DIRECTORY
   */
  class DIRECTORY: public REPOS{//tolua_export
  public:
    //tolua_begin
    DIRECTORY();
    virtual ~DIRECTORY();
    //tolua_end
  protected:
    virtual STREAM* stream(PATH path, STREAM::MODE mode=STREAM::inp);
    virtual void stream(STREAM* stm);
    virtual RESOURCE::TYPE restype(PATH path);
    virtual STREAM::MODE resmode(PATH path);
  };//tolua_export
  
}//tolua_export


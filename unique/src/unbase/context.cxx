#include"context.hxx"

namespace unbase{
  CONTEXT::CONTEXT():vendor("{None}"),renderer("{null}"),version("{none}"),extensions("{not found}"){}
  CONTEXT::~CONTEXT(){}
  bool CONTEXT::open(){}
  void CONTEXT::close(){}
  void CONTEXT::bind(){}
  void CONTEXT::ubind(){}
  void CONTEXT::RendererInfo(){}
  void CONTEXT::clear(){}
  CONTEXT::operator string(){return "CONTEXT()";}

  CTXGROUP::CTXGROUP(){}
  CTXGROUP::~CTXGROUP(){}
  
  /*
  __GROUP_TRY_GET_CXXCODE_(unbase::CTXGROUP,
			   unbase::CONTEXT,
			   context,"local CONTEXT=unbase.CONTEXT"
			   )
  */
  
  __GROUP_IMPLEMENTATION_(unbase::CTXGROUP,
			  unbase::CONTEXT,
			  ,
			  ,
			  );
  /*
    CONTEXT* &CONTEXTS::operator[](string name){
    //if(node)array.insert(std::make_pair(name,node));
    //else array.erase(name);
    return array[name];
    }
  */
  CTXGROUP::operator string(){
    string ret="{";
    for(ITER i=begin();i!=end();i++){
      if(!i->second)continue;
      ret+=(*i).first+"="+static_cast<string>(*(*i).second)+",";
    }
    if(ret[ret.length()-1]==',')ret[ret.length()-1]='}';else ret+="}";
    return ret;
  }
}

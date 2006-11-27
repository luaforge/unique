#define IOSTREAM_ENABLE         // Компилить с использованием IOSTREAM
#define SUPPORT_LLFILE          // Низкоуровневый файловый хендлинг
#define LLFILE_BUFSIZE 65536    // Размер буффера для файловых операций
#define DEFAULT_VBO_ENABLE true // Разрешение VBO рендеринг по умолчанию
#define OGL_DEBUG_MODE          // OpenGL debug mode
//# define MEM_DEBUG_MODE          // Memory debug mode
//# define COMPILE_GLMATRIXOP      // Матрицы будет считать GPU
#define MAX_KEYS_STATE 8        // Максимальное число одновременно изменяющих состояние клавиш
//# define SUPPORT_BZIP2           // Поддержка компрессии bz2
//# define SUPPORT_TEXTURE_DDS      // Поддержка текстур ДДС
//#undef _WIN32
#define LUNIQUE_HXX_PATH ../../src/
#define LUNIQUE_HXX_EXT .hxx
#define UNHEADER(name) <../../src/name/name.hxx>

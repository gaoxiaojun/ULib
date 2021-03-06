// test_services.cpp

#include <ulib/command.h>
#include <ulib/utility/base64.h>
#include <ulib/utility/services.h>

#include <iostream>

#define TESTOA "button:\taddDocument\tAdd\taddDocument\nbutton:\tsaveDocument\tSave\tsaveDocument\n#frame:\tbuiltinSave\tDocument\t-fill both -expand yes\n#@builtinSave\ttext\t\n#button:\tdebugDocument\tDebug\tdebugDocument builtinSave.text"

#define TESTOB "YnV0dG9uOglhZGREb2N1bWVudAlBZGQJYWRkRG9jdW1lbnQKYnV0dG9uOglzYXZlRG9jdW1l\nbnQJU2F2ZQlzYXZlRG9jdW1lbnQKI2ZyYW1lOglidWlsdGluU2F2ZQlEb2N1bWVudAktZmls\nbCBib3RoIC1leHBhbmQgeWVzCiNAYnVpbHRpblNhdmUJdGV4dAkKI2J1dHRvbjoJZGVidWdE\nb2N1bWVudAlEZWJ1ZwlkZWJ1Z0RvY3VtZW50IGJ1aWx0aW5TYXZlLnRleHQ=\n"

int
U_EXPORT main (int argc, char* argv[])
{
   U_ULIB_INIT(argv);

   U_TRACE(5,"main(%d)",argc)

   U_ASSERT_EQUALS( UServices::dosMatchWithOR(U_CONSTANT_TO_PARAM("www.sito1.com"), U_CONSTANT_TO_PARAM("SSI|benchmark|www.sito1.com|www.sito2.com"), FNM_INVERT), false)

   UString buffer(2000);

   u_base64_max_columns = 72;

   UBase64::encode(U_CONSTANT_TO_PARAM(TESTOA), buffer);

   U_INTERNAL_DUMP("buffer = %#.*S", U_STRING_TO_TRACE(buffer))

   U_ASSERT( buffer == U_STRING_FROM_CONSTANT(TESTOB) )

   UBase64::decode( U_CONSTANT_TO_PARAM(TESTOB), buffer);

   U_ASSERT( buffer == U_STRING_FROM_CONSTANT(TESTOA) )

   UString cmd, result1, result2;
   int fd_stderr = U_SYSCALL(open, "%S,%d", "err/services.err", O_WRONLY);

   cmd = U_STRING_FROM_CONSTANT("ls test_services.cpp");
   result1 = UCommand::outputCommand(cmd);

// U_ASSERT( result1 == U_STRING_FROM_CONSTANT("test_services.cpp\n") )

   buffer = UServices::getUUID();
   U_INTERNAL_DUMP("buffer = %#.*S", U_STRING_TO_TRACE(buffer))

   cmd = U_STRING_FROM_CONSTANT("cat test_services.cpp");
   result2 = UCommand::outputCommand(cmd, 0, -1, fd_stderr);

   U_ASSERT( result2.empty() == false )

   cout.write(result2.data(), result2.size());
}

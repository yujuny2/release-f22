if(EXISTS "/workspaces/cs225/release-f22/mp_stickers/build/test_tests-b12d07c.cmake")
  include("/workspaces/cs225/release-f22/mp_stickers/build/test_tests-b12d07c.cmake")
else()
  add_test(test_NOT_BUILT-b12d07c test_NOT_BUILT-b12d07c)
endif()

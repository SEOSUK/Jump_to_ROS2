cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

	find_package(rclcpp REQUIRED)
	find_package(std_msgs REQUIRED)	#두줄 추가하래서 했습니다.
	find_package(geometry_msgs REQUIRED)
	
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()




##노드를 하나 만들때마다 아래 뭉탱이 하나씩 복붙하기 (ros1 느낌 알잘딱)
	add_executable(talker src/publisher_member_function.cpp)  
	ament_target_dependencies(talker rclcpp std_msgs)
	install(TARGETS
	  talker
	  DESTINATION lib/${PROJECT_NAME})
#노드 실행시 이름:talker, 노드 cpp파일: publisher_member_function.cpp


	add_executable(listener src/subscriber_member_function.cpp)
	ament_target_dependencies(listener rclcpp std_msgs)
	install(TARGETS
	  talker
	  listener
	  DESTINATION lib/${PROJECT_NAME})


	add_executable(turtlesim_mover src/turtlesim_mover.cpp)
	ament_target_dependencies(turtlesim_mover
	"rclcpp" 
	"std_msgs"
	"geometry_msgs"
	)
	install(TARGETS
	  turtlesim_mover
	  DESTINATION lib/${PROJECT_NAME})





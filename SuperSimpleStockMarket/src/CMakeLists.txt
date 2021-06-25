set(SRC_FILES
    "StockMarket.cpp"
)

set(HDR_FILES
    "include/StockMarket.hpp"
)

add_library(
    SimpleStockMarket
    ${HDR_FILES}
    ${SRC_FILES})
    
target_include_directories(SimpleStockMarket PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
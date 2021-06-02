cmake_minimum_required(VERSION 3.12.2)

project(DataCreation)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(DataCreation
  Core/CoreUnitTests.cpp
  Core/Debugging/Headers/Declarations.h
  Core/Debugging/Headers/Macros.h
  Core/Functionality/Headers/Event.h
  Core/Functionality/Headers/Function.h
  Core/Functionality/Headers/LockerBase.h
  Core/Functionality/Headers/Scheduler.h
  Core/Functionality/Headers/Subscription.h
  Core/Functionality/Source/Scheduler.cpp
  Core/Functionality/Source/Subscription.cpp
  Core/Geometric/Headers/Ellipsoid.h
  Core/Geometric/Headers/Ellipsoid2.h
  Core/Geometric/Headers/Ellipsoid3.h
  Core/Geometric/Headers/Ellipsoid4.h
  Core/Geometric/Headers/EllipsoidFunctions.h
  Core/Geometric/Headers/Line.h
  Core/Geometric/Headers/Line2.h
  Core/Geometric/Headers/Line3.h
  Core/Geometric/Headers/Line4.h
  Core/Geometric/Headers/LineFunctions.h
  Core/Geometric/Headers/Plane.h
  Core/Geometric/Headers/Plane2.h
  Core/Geometric/Headers/Plane3.h
  Core/Geometric/Headers/Plane4.h
  Core/Geometric/Headers/PlaneFunctions.h
  Core/Geometric/Headers/Transform.h
  Core/Geometric/Headers/UtilityFunctions.h
  Core/Headers/AllCore.h
  Core/Headers/CoreDefs.h
  Core/Headers/Exception.h
  Core/Headers/Hash.h
  Core/Headers/ListDefs.h
  Core/Headers/MapDefs.h
  Core/Headers/PtrDefs.h
  Core/Headers/TemplateDefs.h
  Core/Headers/TimeDefs.h
  Core/IO/Headers/Exception.h
  Core/IO/Headers/File.h
  Core/IO/Headers/Folder.h
  Core/IO/Headers/IODefs.h
  Core/IO/Headers/IOUtils.h
  Core/IO/Source/File.cpp
  Core/IO/Source/Folder.cpp
  Core/IO/Source/IOUtils.cpp
  Core/Math/Headers/Axis.h
  Core/Math/Headers/Basis.h
  Core/Math/Headers/Color.h
  Core/Math/Headers/MathDefs.h
  Core/Math/Headers/MathUtils.h
  Core/Math/Headers/Matrix.h
  Core/Math/Headers/Matrix2x2.h
  Core/Math/Headers/Matrix3x3.h
  Core/Math/Headers/Matrix4x4.h
  Core/Math/Headers/MatrixFunctions.h
  Core/Math/Headers/Quaternion.h
  Core/Math/Headers/QuaternionFunctions.h
  Core/Math/Headers/UtilityFunctions.h
  Core/Math/Headers/Vector.h
  Core/Math/Headers/Vector2.h
  Core/Math/Headers/Vector3.h
  Core/Math/Headers/Vector4.h
  Core/Math/Headers/VectorFunctions.h
  Core/Math/UnitTests/MathUnitTests.h
  Core/Math/UnitTests/MatrixTests.cpp
  Core/Math/UnitTests/MatrixTests.h
  Core/Math/UnitTests/VectorTests.cpp
  Core/Math/UnitTests/VectorTests.h
  Core/Serialization/Headers/Serialization.h
  Core/Serialization/Headers/SerializationDefs.h
  Core/Serialization/Headers/SerializationUtils.h
  Core/Source/Exception.cpp
  Core/Source/Hash.cpp
  Core/Threading/Headers/Job.h
  Core/Threading/Headers/JobHandle.h
  Core/Threading/Headers/JobManager.h
  Core/Threading/Headers/Semaphore.h
  Core/Threading/Headers/Thread.h
  Core/Threading/Headers/ThreadDefs.h
  Core/Threading/Headers/ThreadManager.h
  Core/Threading/Source/Job.cpp
  Core/Threading/Source/JobHandle.cpp
  Core/Threading/Source/JobManager.cpp
  Core/Threading/Source/Semaphore.cpp
  Core/Threading/Source/Thread.cpp
  Core/Threading/Source/ThreadManager.cpp
  Core/UnitTests/HashTesting.cpp
  Core/UnitTests/HashTesting.h
  Data/Data.h
  Data/Headers/AssetData.h
  Data/Headers/AssetExceptions.h
  Data/Headers/AssetName.h
  Data/Headers/AssetType.h
  Data/Headers/AssetUtils.h
  Data/ListTest.h
  Data/PrimaryForeignKeyTest.h
  Data/Rendering/Headers/AnimatedMeshData.h
  Data/Rendering/Headers/AnimatedModelData.h
  Data/Rendering/Headers/MaterialData.h
  Data/Rendering/Headers/SimpleMeshData.h
  Data/Rendering/Headers/SimpleModelData.h
  Data/Rendering/Headers/SkeletonAnimationData.h
  Data/Rendering/Headers/SkeletonData.h
  Data/Rendering/Headers/StaticMeshData.h
  Data/Rendering/Headers/StaticModelData.h
  Data/Rendering/Headers/TextureData.h
  Data/Rendering/Headers/VertexBaseData.h
  Data/Rendering/Source/AnimatedMeshData.cpp
  Data/Rendering/Source/AnimatedModelData.cpp
  Data/Rendering/Source/MaterialData.cpp
  Data/Rendering/Source/SimpleMeshData.cpp
  Data/Rendering/Source/SimpleModelData.cpp
  Data/Rendering/Source/SkeletonAnimationData.cpp
  Data/Rendering/Source/SkeletonData.cpp
  Data/Rendering/Source/StaticMeshData.cpp
  Data/Rendering/Source/StaticModelData.cpp
  Data/Rendering/Source/TextureData.cpp
  Data/Source/AssetUtils.cpp
  Data/Test.h
  Data/Test2.h
  DataExport.cpp
  DataExport/CustomData/Headers/DataCreation.h
  DataExport/CustomData/Headers/DataExportDefs.h
  DataExport/CustomData/Headers/DataExportUtils.h
  DataExport/CustomData/Source/DataCreation.cpp
  DataExport/CustomData/Source/DataExportDefs.cpp
  DataExport/CustomData/Source/DataExportUtils.cpp
  DataExport/Headers/AssetExportDefs.h
  DataExport/Headers/ExportData.h
  DataExport/Headers/ExportException.h
  DataExport/Rendering/Headers/AssimpExtensions.h
  DataExport/Rendering/Headers/MaterialExport.h
  DataExport/Rendering/Headers/MeshExport.h
  DataExport/Rendering/Headers/ModelExport.h
  DataExport/Rendering/Headers/SceneConversion.h
  DataExport/Rendering/Headers/SkeletonAnimationExport.h
  DataExport/Rendering/Headers/SkeletonExport.h
  DataExport/Rendering/Headers/TextureExport.h
  DataExport/Rendering/Headers/Utils.h
  DataExport/Rendering/Source/AssimpExtensions.cpp
  DataExport/Rendering/Source/MaterialExport.cpp
  DataExport/Rendering/Source/MeshExport.cpp
  DataExport/Rendering/Source/ModelExport.cpp
  DataExport/Rendering/Source/SceneConversion.cpp
  DataExport/Rendering/Source/SkeletonAnimationExport.cpp
  DataExport/Rendering/Source/SkeletonExport.cpp
  DataExport/Rendering/Source/TextureExport.cpp
  DataExport/Rendering/Source/Utils.cpp
  DataExport/Resources/ExportedAssets/Assets.h
  DataExport/Resources/ExportedAssets/CustomAssets.h
  DataExport/Resources/ExportedAssets/MaterialAssets.h
  DataExport/Resources/ExportedAssets/MeshAssets.h
  DataExport/Source/ExportData.cpp
  DataExport/SQL/Headers/SQLDefs.h
  DataExport/SQL/Headers/SQLExceptions.h
  DataExport/SQL/Headers/SQLInstance.h
  DataExport/SQL/Source/SQLInstance.cpp
  Dependencies/Includes/ASSIMP/ai_assert.h
  Dependencies/Includes/ASSIMP/anim.h
  Dependencies/Includes/ASSIMP/camera.h
  Dependencies/Includes/ASSIMP/cexport.h
  Dependencies/Includes/ASSIMP/cfileio.h
  Dependencies/Includes/ASSIMP/cimport.h
  Dependencies/Includes/ASSIMP/color4.h
  Dependencies/Includes/ASSIMP/Compiler/poppack1.h
  Dependencies/Includes/ASSIMP/Compiler/pstdint.h
  Dependencies/Includes/ASSIMP/Compiler/pushpack1.h
  Dependencies/Includes/ASSIMP/config.h
  Dependencies/Includes/ASSIMP/DefaultLogger.hpp
  Dependencies/Includes/ASSIMP/defs.h
  Dependencies/Includes/ASSIMP/Exporter.hpp
  Dependencies/Includes/ASSIMP/Importer.hpp
  Dependencies/Includes/ASSIMP/importerdesc.h
  Dependencies/Includes/ASSIMP/IOStream.hpp
  Dependencies/Includes/ASSIMP/IOSystem.hpp
  Dependencies/Includes/ASSIMP/light.h
  Dependencies/Includes/ASSIMP/Logger.hpp
  Dependencies/Includes/ASSIMP/LogStream.hpp
  Dependencies/Includes/ASSIMP/material.h
  Dependencies/Includes/ASSIMP/matrix3x3.h
  Dependencies/Includes/ASSIMP/matrix4x4.h
  Dependencies/Includes/ASSIMP/mesh.h
  Dependencies/Includes/ASSIMP/metadata.h
  Dependencies/Includes/ASSIMP/NullLogger.hpp
  Dependencies/Includes/ASSIMP/postprocess.h
  Dependencies/Includes/ASSIMP/ProgressHandler.hpp
  Dependencies/Includes/ASSIMP/quaternion.h
  Dependencies/Includes/ASSIMP/scene.h
  Dependencies/Includes/ASSIMP/texture.h
  Dependencies/Includes/ASSIMP/types.h
  Dependencies/Includes/ASSIMP/vector2.h
  Dependencies/Includes/ASSIMP/vector3.h
  Dependencies/Includes/ASSIMP/version.h
  Dependencies/Includes/SQLite/sqlite3.h
  Dependencies/Includes/SQLite/sqlite3ext.h
  SampleExportFormat/ExportedAssets/Assets.h
  SampleExportFormat/ExportedAssets/CustomAssets.h
  SampleExportFormat/ExportedAssets/MaterialAssets.h
  SampleExportFormat/ExportedAssets/MeshAssets.h
)
# Additional include directories
set_property(TARGET DataCreation
  APPEND PROPERTY INCLUDE_DIRECTORIES
  $<$<CONFIG:Debug>:
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Includes/ASSIMP;
    ${CMAKE_CURRENT_SOURCE_DIR}/../DataCreation;
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Includes;
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Includes/SQLite>
  $<$<CONFIG:Release>:
    C:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation/Dependencies/Includes/ASSIMP;
    C:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation;
    C:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation/Dependencies/Includes>
)

# Preprocessor definitions
target_compile_definitions(DataCreation PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;WIN32;assimp_BUILD_BOOST_WORKAROUND;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;WIN32;assimp_BUILD_BOOST_WORKAROUND;NDEBUG;_CONSOLE>
)

# Minimal rebuild
if (MSVC)
  target_compile_options(DataCreation PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(DataCreation PRIVATE
    ""
  )
endif ()

# Additional library directories
if (MSVC)
  target_link_options(DataCreation PRIVATE
    $<$<CONFIG:Debug>:
      /LIBPATH:${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Libs/ASSIMP
      /LIBPATH:${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Libs/SQLite>
    $<$<CONFIG:Release>:
      /LIBPATH:C:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation/Dependencies/Libs/SQLite
      /LIBPATH:C:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation/Dependencies/Libs/ASSIMP>
  )
else ()
  target_link_options(DataCreation PRIVATE
    $<$<CONFIG:Debug>:
      -L${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Libs/ASSIMP
      -L${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Libs/SQLite>
    $<$<CONFIG:Release>:
      -LC:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation/Dependencies/Libs/SQLite
      -LC:/Users/Jagger/Desktop/Coding/VisualStudios/DataCreation/DataCreation/Dependencies/Libs/ASSIMP>
  )
endif ()

# Link libraries
set_property(TARGET DataCreation
  APPEND PROPERTY LINK_LIBRARIES
  "$<$<CONFIG:Debug>:sqlite3.lib;assimp.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib>"
  "$<$<CONFIG:Release>:sqlite3.lib;assimp.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib>"
)

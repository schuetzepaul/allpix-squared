#include <iostream>
#include <ostream>
#include <vector>
#include <memory>
#include <utility>
#include <string>

#include "../core/AllPix.hpp"

#include "../core/module/StaticModuleManager.hpp"
#include "../core/config/SimpleConfigManager.hpp"
#include "../core/geometry/GeometryManager.hpp"

#include "../core/utils/exceptions.h"
#include "../core/utils/log.h"

//#include "../tools/runge_kutta.h"

//#include "examples.h"

#include "../core/module/UniqueModuleFactory.hpp"

//FIXME: should not be here
#include "../modules/geometry_test/GeometryConstructionModule.hpp"
#include "../modules/deposition_simple/SimpleDepositionModule.hpp"
#include "../modules/visualization_test/TestVisualizationModule.hpp"


using namespace allpix;

// FIXME: temporary generator function for as long we do not have dynamic loading
std::unique_ptr<ModuleFactory> generator(std::string str){
    if(str == GeometryConstructionModule::name) return std::make_unique<UniqueModuleFactory<GeometryConstructionModule>>();
    if(str == SimpleDepositionModule::name) return std::make_unique<UniqueModuleFactory<SimpleDepositionModule>>();
    if(str == TestVisualizationModule::name) return std::make_unique<UniqueModuleFactory<TestVisualizationModule>>();

    return nullptr;
}

int main(int, const char **) {
    std::string file_name = "etc/example.ini";
    
    try {
        // Set global log level:
        LogLevel log_level = Log::getLevelFromString("DEBUG");
        Log::setReportingLevel(log_level);
        LOG(INFO) << "Set log level: " << Log::getStringFromLevel(log_level);
            
        // Construct managers (FIXME: move some initialization to AllPix)
        std::unique_ptr<GeometryManager> geo = std::make_unique<GeometryManager>();
        std::unique_ptr<StaticModuleManager> mod = std::make_unique<StaticModuleManager>(&generator);
        std::unique_ptr<SimpleConfigManager> conf = std::make_unique<SimpleConfigManager>(file_name);
        
        // Construct main AllPix object
        std::unique_ptr<AllPix> apx = std::make_unique<AllPix>(std::move(conf), std::move(mod), std::move(geo));
        
        LOG(INFO) << "Initializing AllPix";
        apx->init();
        
        LOG(INFO) << "Running AllPix";
        apx->run();
        
        LOG(INFO) << "Finishing AllPix";
        apx->finalize();
    } catch (ConfigurationError &e) {
        LOG(CRITICAL) << "Error in the configuration file:";
        LOG(CRITICAL) << "   " << e.what(); 
        LOG(CRITICAL) << "The configuration file needs to be updated! Cannot continue...";
    } catch (RuntimeError &e) {
        LOG(CRITICAL) << "Error during execution of run:";
        LOG(CRITICAL) << "   " << e.what(); 
        LOG(CRITICAL) << "Please check your configuration and modules! Cannot continue...";
    } catch (LogicError &e) {
        LOG(CRITICAL) << "Error in the logic of module:";
        LOG(CRITICAL) << "   " << e.what(); 
        LOG(CRITICAL) << "Module has to be properly defined! Cannot continue...";
    } catch(std::exception &e) { 
        LOG(CRITICAL) << "Fatal internal error";
        LOG(CRITICAL) << "   " << e.what(); 
        LOG(CRITICAL) << "Cannot continue...";
    }
        
    return 0;
}

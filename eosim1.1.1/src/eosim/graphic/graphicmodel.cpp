//#include <eosim/graphic/graphicmodel.hpp>
//#include <eosim/graphic/refreshgraphic.hpp>
//
//using namespace eosim::core;
//using namespace eosim::graphic;
//
//RefreshGraphic::RefreshGraphic(GraphicModel& model): CEvent(model) {}
//
//RefreshGraphic::~RefreshGraphic() {}
//
//void RefreshGraphic::eventRoutine() {
//	GraphicModel& gm = dynamic_cast<GraphicModel&>(owner);
//	gm.d.advance(gm.getSimTime() - gm.lastTime);
//	gm.lastTime = gm.getSimTime();
//}
//
//
//GraphicModel::GraphicModel(int width, int height): rg(*this), d(width, height), lastTime(0) {}
//
//GraphicModel::~GraphicModel() {}
//
//void GraphicModel::init() {
//	registerCEvent(&rg);
//}
//
//void GraphicModel::doInitialSchedules() {}
//

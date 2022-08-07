cmake_minimum_required(VERSION 3.22)

add_library(Core framework.h
            Net/NetClient.h Net/NetServer.h Net/NetServer.cpp
            Models/Board.h
            Views/BoardView.h
            Controllers/BoardController.h
            Rules/Rules.h
            Rules/MoveRule.h Rules/CaptureRule.h
            Rules/MoveKingRule.h Rules/CaptureKingRule.h
            Rules/BecomeKingRule.h
            Rules/EndGameRule.h Views/WinView.h Views/LoseView.h Net/NetClient.cpp Views/WaitingView.h)

set_target_properties(Core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Core PUBLIC cxx_std_20)

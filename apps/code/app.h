#ifndef CODE_APP_H
#define CODE_APP_H

#include <escher.h>
#include <ion/events.h>
#include "console_controller.h"
#include "menu_controller.h"
#include "script_store.h"
#include "python_toolbox.h"
#include "variable_box_controller.h"

namespace Code {

class App : public ::App {
public:
  class Descriptor : public ::App::Descriptor {
  public:
    I18n::Message name() override;
    I18n::Message upperName() override;
    const Image * icon() override;
  };
  class Snapshot : public ::App::Snapshot {
  public:
    Snapshot();
    App * unpack(Container * container) override;
    void reset() override;
    Descriptor * descriptor() override;
    ScriptStore * scriptStore();
#if EPSILON_GETOPT
    bool lockOnConsole() const;
    void setOpt(const char * name, char * value) override;
#endif
  private:
#if EPSILON_GETOPT
    bool m_lockOnConsole;
#endif
    ScriptStore m_scriptStore;
  };
  ~App();
  StackViewController * stackViewController() { return &m_codeStackViewController; }
  ConsoleController * consoleController() { return &m_consoleController; }
  PythonToolbox * pythonToolbox() { return &m_toolbox; }
  bool handleEvent(Ion::Events::Event event) override;
  bool textInputDidReceiveEvent(TextInput * textInput, Ion::Events::Event event);
  // Python delegate
  bool pythonIsInited() { return m_pythonUser != nullptr; }
  bool isPythonUser(const void * pythonUser) { return m_pythonUser == pythonUser; }
  void initPythonWithUser(const void * pythonUser);
  void deinitPython();
private:
  /* Python delegate:
   * MicroPython requires a heap. To avoid dynamic allocation, we keep a working
   * buffer here and we give to controllers that load Python environment. We
   * also memoize the last Python user to avoid re-initiating MicroPython when
   * unneeded. */
  static constexpr int k_pythonHeapSize = 16384;
  char m_pythonHeap[k_pythonHeapSize];
  const void * m_pythonUser;

  App(Container * container, Snapshot * snapshot);
  ConsoleController m_consoleController;
  ButtonRowController m_listFooter;
  MenuController m_menuController;
  StackViewController m_codeStackViewController;
  PythonToolbox m_toolbox;
  VariableBoxController m_variableBoxController;
};

}

#endif

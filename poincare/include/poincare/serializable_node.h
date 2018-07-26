#ifndef POINCARE_SERIALIZABLE_NODE_H
#define POINCARE_SERIALIZABLE_NODE_H

#include <poincare/tree_node.h>
#include <poincare/print_float.h>

namespace Poincare {

class SerializableNode : public TreeNode {
public:
  using TreeNode::TreeNode;
  virtual bool needsParenthesisWithParent(SerializableNode * parentNode) { return false; } //TODO
  virtual int writeTextInBuffer(char * buffer, int bufferSize, PrintFloat::Mode floatDisplayMode = PrintFloat::Mode::Decimal, int numberOfSignificantDigits = 0) const = 0;

};

}

#endif
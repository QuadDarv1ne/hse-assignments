class TreeNode:
    """
    Класс для узла дерева
    """
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class ExpressionTree:
    """
    Класс для построения и вычисления синтаксического дерева арифметического выражения
    """
    def __init__(self):
        self.operators = {'+', '-', '*', '/'}

    def is_operator(self, char):
        return char in self.operators

    def build_tree(self, postfix):
        """
        Построение дерева из постфиксной записи
        :param postfix: Список символов в постфиксной нотации
        :return: Корень дерева
        """
        stack = []

        for char in postfix:
            node = TreeNode(char)

            if self.is_operator(char):
                # Достаём два операнда из стека
                node.right = stack.pop()
                node.left = stack.pop()

            stack.append(node)

        return stack.pop()

    def evaluate(self, root):
        """
        Вычисление значения выражения, представленного деревом
        :param root: Корень дерева
        :return: Результат вычисления
        """
        if root is None:
            return 0

        if not self.is_operator(root.value):
            return int(root.value)

        left_val = self.evaluate(root.left)
        right_val = self.evaluate(root.right)

        if root.value == '+':
            return left_val + right_val
        elif root.value == '-':
            return left_val - right_val
        elif root.value == '*':
            return left_val * right_val
        elif root.value == '/':
            return left_val / right_val

# Пример использования
if __name__ == "__main__":
    expression = "3 4 + 2 * 7 /"  # Постфиксная запись (эквивалентно: ((3 + 4) * 2) / 7)
    postfix = expression.split()

    tree = ExpressionTree()
    root = tree.build_tree(postfix)

    print("Результат вычисления выражения:", tree.evaluate(root))

/*
    Тема №2. Абстрактные типы данных (нелинейные структуры) – 4 часа
    
    АТД «дерево» - лексический разбор арифметического выражения
*/

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>

using namespace std;

// Узел дерева
struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

class ExpressionTree {
public:
    // Построение дерева из постфиксной записи
    TreeNode* buildTree(const vector<string>& postfix) {
        stack<TreeNode*> st;

        for (const string& token : postfix) {
            TreeNode* node = new TreeNode(token);

            if (isOperator(token)) {
                // Достаем два операнда из стека
                node->right = st.top(); st.pop();
                node->left = st.top(); st.pop();
            }

            st.push(node);
        }

        return st.top();
    }

    // Вычисление значения выражения
    double evaluate(TreeNode* root) {
        if (!root) return 0;

        if (!isOperator(root->value)) {
            return stod(root->value);
        }

        double leftVal = evaluate(root->left);
        double rightVal = evaluate(root->right);

        if (root->value == "+") return leftVal + rightVal;
        if (root->value == "-") return leftVal - rightVal;
        if (root->value == "*") return leftVal * rightVal;
        if (root->value == "/") return leftVal / rightVal;

        return 0;
    }

private:
    // Проверка, является ли строка оператором
    bool isOperator(const string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }
};

int main() {
    string expression = "3 4 + 2 * 7 /"; // Постфиксная запись
    vector<string> postfix;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        postfix.push_back(token);
    }

    ExpressionTree tree;
    TreeNode* root = tree.buildTree(postfix);

    cout << "Результат вычисления выражения: " << tree.evaluate(root) << endl;

    return 0;
}

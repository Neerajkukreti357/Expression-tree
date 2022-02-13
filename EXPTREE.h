#include<stack>

using namespace std;

//NODE STRUCTURE FOR CREATING EXPRESSION TREE
struct Node
{
    Node* left = nullptr;
    char data = NULL;
    Node* right = nullptr;
};

class generate_exp
{
    Node* root = nullptr;

public:
    generate_exp(string exp_from_user);
    int check_precedence(char ope);
    bool is_operand(char ch);
    Node* giv_me();
    ~generate_exp();
};

//constructor
generate_exp::generate_exp(string exp_from_user)
{
    //stack char is only contains operator
    stack<char> operator_stack;

    //stack for Nodes of the tree
    stack<Node*> Node_stack;

    //scanning of string and generating expression tree
    for(int i=0;i<exp_from_user.length();i++)
    {
        if(is_operand(exp_from_user[i]))
        {
            Node* new_node = new Node;

            //inserting operand to new Node
            new_node->data = exp_from_user[i];
            Node_stack.push(new_node);
        }
        else
        {
            if(operator_stack.empty() || check_precedence(operator_stack.top()) < check_precedence(exp_from_user[i]))
            {
                operator_stack.push(exp_from_user[i]);
            }
            else if(check_precedence(operator_stack.top()) > check_precedence(exp_from_user[i]))
            {
                Node* left_node,*right_node,*new_node = nullptr;
                right_node = Node_stack.top();
                Node_stack.pop();

                left_node = Node_stack.top();
                Node_stack.pop();

                new_node = new Node;
                new_node->data = operator_stack.top();
                operator_stack.pop();

                new_node->left = left_node;
                new_node->right = right_node;

                operator_stack.push(exp_from_user[i]);
                Node_stack.push(new_node);

            }//end of inner else if statement
        }//end of outer else statement
    }//end of for loop

    while(!operator_stack.empty())
    {

                Node* left_node,*right_node,*new_node = nullptr;
                right_node = Node_stack.top();
                Node_stack.pop();

                left_node = Node_stack.top();
                Node_stack.pop();

                new_node = new Node;
                new_node->data = operator_stack.top();
                operator_stack.pop();

                new_node->left = left_node;
                new_node->right = right_node;

                Node_stack.push(new_node);
    }//end of while loop

    root = Node_stack.top();
}

//distructor
generate_exp::~generate_exp()
{
    delete root;
}

//is_operator class method defination
bool generate_exp::is_operand(char ch)
{
    if(ch == '(' ||ch == ')' ||ch == '+' ||ch == '-' ||ch == '/' ||ch == '*' ||ch == '^')
        return false;
    else
        return true;
}

//check_precedence operator method defination
int generate_exp::check_precedence(char ope)
{
    if(ope == '+' || ope == '-')
        return 1;
    else if(ope == '*' || ope == '/')
        return 4;
    else if(ope == '^')
        return 8;
    else if(ope == '(')
        return 12;
}

//display method defination
Node* generate_exp::giv_me()
{
    return root;
}

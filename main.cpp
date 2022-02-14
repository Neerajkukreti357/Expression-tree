#include <iostream>
#include "EXPTREE.h"

using namespace std;

void display(Node* root)
{
    if(root)
    {
        display(root->left);
        display(root->right);
        cout<<root->data;
    }
}

int main()
{
    generate_exp a("(a*(b*(((c+a)+b)*c)))");
    display(a.giv_me());
    return 0;
}

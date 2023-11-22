struct node {
    node () { left = nullptr; right = nullptr; }
    int data;
    node *left;
    node *right;
};

bool f_h (node *t, int k, int temp) {
    if (temp == k && (t->left == t->right == nullptr)) return true;
    else if (temp > k) return false;
    else {
        if (t->left == nullptr && t->right == nullptr) return false;
        else if (t->left == nullptr) return f_h(t->right, k, temp + t->right->data);
        else if (t->right == nullptr) return f_h(t->left, k, temp + t->left->data);
        else return (f_h(t->right, k, temp + t->right->data) || f_h(t->left, k, temp + t->left->data));
    }   
}   

bool func (node *t, int k) {
    if (t == nullptr) return false;
    else return f_h(t, k, t->data);
}


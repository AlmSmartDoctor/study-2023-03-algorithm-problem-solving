class Tree(object):
    def __init__(self, root, left=None, right=None):
        assert root and type(root) == Node
        if left: assert type(left) == Tree and left.root < root
        if right: assert type(right) == Tree and root < right.root

        self.left = left
        self.root = root
        self.right = right
        
    def is_leaf(self):
        return not(self.left or self.right)
        
    
    def __str__(self):
        if self.is_leaf(): 
            return "[%s]" % self.root 
        return "[%s %s %s]" % (self.left if self.left else "_", 
                               self.root,
                               self.right if self.right else "_")
        
    
    def __eq__(self, other):
        if not other: 
            return False 
        if self.root == other.root and \
        self.left == other.left and \
        self.right == other.right: 
            return True 
        return False
    
    def __ne__(self, other):
        if not other: 
            return True
        if self.root != other.root or \
        self.left != other.left or \
        self.right != other.right:  
            return True
        return False

class Node(object):
    
    def __init__(self, value, weight=1):
        self.value = value
        self.weight = weight
    
    def __str__(self):
        return str(self.value)   
    
    def __lt__(self, other):
        return self.value < other.value
    
    def __gt__(self, other):
        return self.value > other.value
    
    def __eq__(self, other):
        return self.value == other.value 

    def __ne__(self, other):
        return self.value != other.value 
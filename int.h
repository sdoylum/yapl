typedef enum { typeIdentifierNode, typeFloatValue, typeShortValue, typeCharValue, typeLongValue, typeDoubleValue, typeStringValue, typeIntegerValue, typeOpr } nodeEnum;

typedef enum { f, t } boolean;

typedef struct integerValueNode{
    long value;          
}integerValueNode;

typedef struct doubleValueNode{
    double value;                 
}doubleValueNode;

typedef struct shortValueNode{
    short value;                 
}shortValueNode;

typedef struct stringValueNode{
    char *value;                 
}stringValueNode;

typedef struct stringDefineNode{
    char *value;                  
}stringDefineNode;

typedef struct intDefineNode{                 
    int value;
}intDefineNode;

typedef struct floatDefineNode{                 
    float value;
}floatDefineNode;

typedef struct charDefineNode{                
    char value;
}charDefineNode;

typedef struct shortDefineNode{                
    short value;
}shortDefineNode;

typedef struct doubleDefineNode{             
    double value;
}doubleDefineNode;

typedef struct longDefineNode{                  
    long value;
}longDefineNode;

typedef struct identifierNode{
	char *name;
}identifierNode;

typedef struct valueNode{
	stringDefineNode *strValue;
	intDefineNode *intValue;
	charDefineNode *charValue;
	doubleDefineNode *doubleValue;
	longDefineNode *longValue;
    floatDefineNode *floatValue;
    shortDefineNode *shortValue;
}valueNode;

typedef struct {
    int oper;                   
    int nops;                   
    struct nodeTypeTag *op[1];  
} oprNode;

typedef struct nodeTypeTag{
    nodeEnum type;              

    union {
		integerValueNode intV;
        stringValueNode strV;
		identifierNode ide;
		doubleValueNode douV;
        oprNode opr;       
    };
}nodeType;

typedef struct runTimeValue{
  char *error;
  int *iValue;
  char *cValue;
  char *stValue;
  float *fValue;
  long *lValue;
  double *dValue;
  short *shValue;
  int *boValue;
}runTimeValue;

typedef struct symbolTable{
  char *name;
  struct symbolTable *next;
  struct valueNode value;
}symbolTable;

struct scope{
	boolean active;
	struct symbolTable symTab;
	struct scope *next;
}scope;

runTimeValue *globalRunTimeValue;

symbolTable *globalSymbolTable;
symbolTable *initialize();





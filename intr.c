#include <stdio.h>
#include "int.h"
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

symbolTable *initialize(symbolTable *table){
	table = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	table->name=(char *)malloc(strlen("null")+1);
	strcpy(table->name, "null");
	table->value.intValue = (intDefineNode*)malloc(sizeof(intDefineNode));
	table->value.intValue->value = 0;
	return table;
}


void runTimeValueClear(runTimeValue *table){
	table->error = NULL;
	free(table->iValue);
	table->cValue = NULL;
	table->stValue = NULL;
	free(table->fValue);
	free(table->lValue);
	free(table->dValue);
	free(table->shValue);
}


char *getRunTimeError (runTimeValue *table){
	char *ret=(char *)malloc(strlen(table->error)+1);
	strcpy(ret, table->error);
	return ret;
}


char *getRunTimeStr (runTimeValue *table){
	char *ret=(char *)malloc(strlen(table->stValue)+1);
	strcpy(ret, table->stValue);
	return ret;
}

char *getRunTimeCha (runTimeValue *table){
	char *ret=(char *)malloc(strlen(table->cValue)+1);
	strcpy(ret, table->cValue);
	return ret;
}

float getRunTimeFlo (runTimeValue *table){
	float a = *table->fValue;
	free(table->fValue);
	table->fValue = NULL;
	return a;
}

double getRunTimeDou (runTimeValue *table){
	double a = *table->dValue;
	free(table->dValue);
	table->dValue = NULL;
	return a;
}

long getRunTimeLon (runTimeValue *table){
	long a = *table->lValue;
	free(table->lValue);
	table->lValue = NULL;
	return a;
}

int getRunTimeBoo(runTimeValue *table){
	int a = *table->boValue;
	free(table->iValue);
	table->iValue = NULL;
	return a;

}

short getRunTimeSho (runTimeValue *table){
	short a = *table->shValue;
	free(table->shValue);
	return a;
}



void setRunTimeStr (runTimeValue *table, char* value){
	table->stValue = (char *)malloc(strlen(value)+1);
	strcpy(table->stValue, value);
}

void setRunTimeCha (runTimeValue *table, char* value){
	table->cValue = (char *)malloc(strlen(value)+1);
	strcpy(table->cValue, value);
}

void setRunTimeFlo (runTimeValue *table, float value){
	table->fValue = (float*)malloc(sizeof(float));
	*table->fValue = value;
}

void setRunTimeDou (runTimeValue *table, double value){
	table->dValue = (double*)malloc(sizeof(double));
	*table->dValue = value;
}

void setRunTimeLon (runTimeValue *table, long value){
	table->lValue = (long*)malloc(sizeof(long));
	*table->lValue = value;
}

void setRunTimeSho (runTimeValue *table, short value){
	table->shValue = (short*)malloc(sizeof(short));
	*table->shValue = value;
}

void setRunTimeBoo (runTimeValue *table, int value){
	table -> boValue = (int*)malloc(sizeof(int));
	*table -> boValue = value;
}


void setSymNoValue(struct symbolTable *table, char *name){
  struct symbolTable *ptr;
  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(name)+1);
	strcpy(ptr->name, name);
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(name)+1);
  strcpy(ptr->name, name);
  table -> next = ptr;
}



void setSymDou(struct symbolTable *table, char *name, double value){
  struct symbolTable *ptr;

  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(name)+1);
	strcpy(ptr->name, name);
	ptr->value.doubleValue = (doubleDefineNode*)malloc(sizeof(doubleDefineNode));
	ptr->value.doubleValue->value = value;
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(name)+1);
  strcpy(ptr->name, name);
  ptr->value.doubleValue = (doubleDefineNode*)malloc(sizeof(doubleDefineNode));
  ptr->value.doubleValue->value = value;
  table -> next = ptr;
}



void setSymInt(struct symbolTable *table, char *name, int value){
  struct symbolTable *ptr;
  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(name)+1);
	strcpy(ptr->name, name);
	ptr->value.intValue = (intDefineNode*)malloc(sizeof(intDefineNode));
	ptr->value.intValue->value = value;
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(name)+1);
  strcpy(ptr->name, name);
  ptr->value.intValue = (intDefineNode*)malloc(sizeof(intDefineNode));
  ptr->value.intValue->value = value;
  table -> next = ptr;
}

void setSymStr (symbolTable *table, char *name, char* value){
  struct symbolTable *ptr;
  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(name)+1);
	strcpy(ptr->name, name);
	ptr->value.strValue = (stringDefineNode*)malloc(sizeof(stringDefineNode));
	strcpy(ptr->value.strValue->value, value);
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(name)+1);
  strcpy(ptr->name, name);
  ptr->value.strValue = (stringDefineNode*)malloc(sizeof(stringDefineNode));
  
  ptr->value.strValue->value = value;
  table -> next = ptr;

}


void setSymCha (symbolTable *table, char *name, char* value){
  struct symbolTable *ptr;
  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(value)+1);
	strcpy(ptr->name, name);
	ptr->value.charValue = (charDefineNode*)malloc(sizeof(charDefineNode));
	strcpy(ptr->value.charValue->value, value);
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(value)+1);
  strcpy(ptr->name, name);
  ptr->value.charValue = (charDefineNode*)malloc(sizeof(charDefineNode));
  strcpy(ptr->value.charValue->value, value);
  table -> next = ptr;
}

void setSymFlo (symbolTable *table, char *name, float value){
  struct symbolTable *ptr;
  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(name)+1);
	strcpy(ptr->name, name);
	ptr->value.floatValue = (floatDefineNode*)malloc(sizeof(floatDefineNode));
	ptr->value.floatValue->value = value;
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(name)+1);
  strcpy(ptr->name, name);
  ptr->value.floatValue = (floatDefineNode*)malloc(sizeof(floatDefineNode));
  ptr->value.floatValue->value = value;
  table -> next = ptr;
}

void setSymLon (symbolTable *table, char *name, long value){
  struct symbolTable *ptr;
  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(name)+1);
	strcpy(ptr->name, name);
	ptr->value.longValue = (longDefineNode*)malloc(sizeof(longDefineNode));
	ptr->value.longValue->value = value;
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(name)+1);
  strcpy(ptr->name, name);
  ptr->value.longValue = (longDefineNode*)malloc(sizeof(longDefineNode));
  ptr->value.longValue->value = value;
  table -> next = ptr;
}


void setSymSho (symbolTable *table, char *name, short value){
  struct symbolTable *ptr;
  if(table == NULL){
	ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
	ptr->name=(char *)malloc(strlen(name)+1);
	strcpy(ptr->name, name);
	ptr->value.shortValue = (shortDefineNode*)malloc(sizeof(shortDefineNode));
	ptr->value.shortValue->value = value;
	table->next = ptr; 
  }
  while(table -> next != NULL){
	  table = table -> next;
  }

  ptr = (struct symbolTable*) malloc(sizeof(struct symbolTable));
  ptr->name=(char *)malloc(strlen(name)+1);
  strcpy(ptr->name, name);
  ptr->value.shortValue = (shortDefineNode*)malloc(sizeof(shortDefineNode));
  ptr->value.shortValue->value = value;
  table -> next = ptr;
}


symbolTable *getsym(struct symbolTable *getSymbolTable, char *sym_name)
{
	struct symbolTable *iter = getSymbolTable;
	while(iter!=NULL){;
		
		if (strcmp (iter->name,sym_name) == 0){
			return iter;
		}
		iter=iter->next;
	} 
	return NULL;
}

void charNodeVisit(nodeType *p){
	setRunTimeLon(globalRunTimeValue, p->intV.value);
}

void intNodeVisit(nodeType *p){
	setRunTimeLon(globalRunTimeValue, p->intV.value);
}

void douNodeVisit(nodeType *p){
	setRunTimeDou(globalRunTimeValue, p->douV.value);
}

void stringNodeVisit(nodeType *p){
	setRunTimeStr(globalRunTimeValue, p->strV.value);
}

void idNodeVisit(nodeType *p){
	symbolTable *vn = getsym(globalSymbolTable, p->ide.name);
	if(vn == NULL){
		printf("Değer bulunamadı.");
	}else if(vn->value.strValue!=NULL){
		setRunTimeStr(globalRunTimeValue, vn->value.strValue->value);
	}else if(vn->value.intValue!=NULL){
		setRunTimeLon(globalRunTimeValue, vn->value.intValue->value);
	}else if(vn->value.shortValue!=NULL){
		setRunTimeLon(globalRunTimeValue, (long) vn->value.shortValue->value);
	}else if(vn->value.doubleValue!=NULL){
		setRunTimeDou(globalRunTimeValue, vn->value.doubleValue->value);
	}else if(vn->value.longValue!=NULL){
		setRunTimeLon(globalRunTimeValue, vn->value.longValue->value);
	}else if(vn->value.floatValue!=NULL){
		setRunTimeDou(globalRunTimeValue, vn->value.floatValue->value);
	}
}

void whileNodeVisit(nodeType *p){
	ex(p->opr.op[0]);
	while(getRunTimeBoo(globalRunTimeValue) == 1){
		ex(p->opr.op[1]);
		ex(p->opr.op[0]);
	}

}

void ifNodeVisit(nodeType *p){
	ex(p->opr.op[0]);

	if (getRunTimeBoo(globalRunTimeValue) == 1){


		ex(p->opr.op[1]);
		
	}
	else if (p->opr.nops > 2){


		ex(p->opr.op[2]);
	}
}

void printNodeVisit(nodeType *p){
	ex(p->opr.op[0]);
	if(globalRunTimeValue->stValue != NULL){
		printf("%s", getRunTimeStr(globalRunTimeValue));
	}else if(globalRunTimeValue->lValue != NULL){
		printf("%ld", getRunTimeLon(globalRunTimeValue));
	}else if(globalRunTimeValue->cValue != NULL){
		printf("%c", getRunTimeCha(globalRunTimeValue));
	}else if(globalRunTimeValue->shValue != NULL){
		printf("%u", getRunTimeSho(globalRunTimeValue));
	}else if(globalRunTimeValue->dValue != NULL){
		printf("%f", getRunTimeDou(globalRunTimeValue));
	}else if(globalRunTimeValue->error != NULL){
		printf("%s", getRunTimeError(globalRunTimeValue));
	}else if(globalRunTimeValue->boValue != NULL){
		if(getRunTimeBoo(globalRunTimeValue) == 1){
			printf("true");
		}else if(getRunTimeBoo(globalRunTimeValue) == 1){
			printf("false");
		}
		
	}   
}

void printlnNodeVisit(nodeType *p){
	ex(p->opr.op[0]);
	if(globalRunTimeValue->stValue != NULL){
		printf("%s\n", getRunTimeStr(globalRunTimeValue));
	}else if(globalRunTimeValue->lValue != NULL){
		printf("%ld\n", getRunTimeLon(globalRunTimeValue));
	}else if(globalRunTimeValue->cValue != NULL){
		printf("%c\n", getRunTimeCha(globalRunTimeValue));
	}else if(globalRunTimeValue->shValue != NULL){
		printf("%u\n", getRunTimeSho(globalRunTimeValue));
	}else if(globalRunTimeValue->dValue != NULL){
		printf("%f\n", getRunTimeDou(globalRunTimeValue));
	}else if(globalRunTimeValue->error != NULL){
		printf("%s\n", getRunTimeError(globalRunTimeValue));
	}else if(globalRunTimeValue->boValue != NULL){
		if(getRunTimeBoo(globalRunTimeValue) == 1){
			printf("true");
		}else if(getRunTimeBoo(globalRunTimeValue) == 1){
			printf("false");
		}
		
	}   
}

void semcolNodeVisit(nodeType *p){
	ex(p->opr.op[0]);
	ex(p->opr.op[1]);
}

void noValueDefineNodeVisit(nodeType *p){
	setSymNoValue(globalSymbolTable, p->opr.op[0]->ide.name);
}


void intDefNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	setSymInt(globalSymbolTable, p->opr.op[0]->ide.name, getRunTimeLon(globalRunTimeValue));
}


void intAssignVisit(nodeType *p){
	symbolTable *vn = getsym(globalSymbolTable, p->opr.op[0]->ide.name);
	ex(p->opr.op[1]);
	vn->value.intValue->value = getRunTimeLon(globalRunTimeValue);
}

void shoDefNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	long a = getRunTimeLon(globalRunTimeValue);
	if(-32768 < a && a < 32767){
		setSymSho(globalSymbolTable, p->opr.op[0]->ide.name, (short) a);
	}else{
		printf("Short icin fazla büyük değer: %d");
	}
}

void strDefNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	setSymStr(globalSymbolTable, p->opr.op[0]->ide.name, getRunTimeStr(globalRunTimeValue));
}

void floDefNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	setSymFlo(globalSymbolTable, p->opr.op[0]->ide.name, getRunTimeDou(globalRunTimeValue));
}

void lonDefNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	setSymDou(globalSymbolTable, p->opr.op[0]->ide.name, getRunTimeDou(globalRunTimeValue));
}


void chaDefNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	setSymDou(globalSymbolTable, p->opr.op[0]->ide.name, getRunTimeDou(globalRunTimeValue));
}


void uminusNodeVisit(nodeType *p){
	ex(p->opr.op[0]);
	setRunTimeLon(globalRunTimeValue, -getRunTimeLon(globalRunTimeValue));
}

void plusNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	if(globalRunTimeValue->lValue != NULL){
		int b = getRunTimeLon(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			setRunTimeLon(globalRunTimeValue, a+b);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a+bb);
		}

	}else if(globalRunTimeValue->dValue != NULL){
		double b = getRunTimeDou(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a+bb);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			setRunTimeDou(globalRunTimeValue, a+b);

		}
	}
}

void minusNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	if(globalRunTimeValue->lValue != NULL){
		int b = getRunTimeLon(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			setRunTimeLon(globalRunTimeValue, a-b);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a-bb);
		}

	}else if(globalRunTimeValue->dValue != NULL){
		double b = getRunTimeDou(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a-bb);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			setRunTimeDou(globalRunTimeValue, a-b);

		}
	}
}

void multiNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	if(globalRunTimeValue->lValue != NULL){
		int b = getRunTimeLon(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			setRunTimeLon(globalRunTimeValue, a*b);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a*bb);
		}

	}else if(globalRunTimeValue->dValue != NULL){
		double b = getRunTimeDou(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a*bb);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			setRunTimeDou(globalRunTimeValue, a*b);

		}
	}
}

void divNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	if(globalRunTimeValue->lValue != NULL){
		int b = getRunTimeLon(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			setRunTimeLon(globalRunTimeValue, a/b);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a/bb);
		}

	}else if(globalRunTimeValue->dValue != NULL){
		double b = getRunTimeDou(globalRunTimeValue);
		ex(p->opr.op[0]);
		if(globalRunTimeValue->lValue != NULL){
			int a = getRunTimeLon(globalRunTimeValue);
			double bb = (double) b;
			setRunTimeDou(globalRunTimeValue, a/bb);
		}else if(globalRunTimeValue->dValue != NULL){
			double a = getRunTimeDou(globalRunTimeValue);
			setRunTimeDou(globalRunTimeValue, a/b);

		}
	}
}

void strCatVisit(nodeType *p){
	
	ex(p->opr.op[0]);
	char *temp = getRunTimeStr(globalRunTimeValue);
	ex(p->opr.op[1]);
	char *temp2 = getRunTimeStr(globalRunTimeValue);
	setRunTimeStr(globalRunTimeValue, strcat(temp,temp2));
	
}



void lessThanNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	int b = getRunTimeLon(globalRunTimeValue);

	ex(p->opr.op[0]);
	int a = getRunTimeLon(globalRunTimeValue);

	if(b < a){
		setRunTimeBoo(globalRunTimeValue, 1);

	}else{
		
		setRunTimeBoo(globalRunTimeValue, 0);
	}
}

void greaterThanNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	int b = getRunTimeLon(globalRunTimeValue);

	ex(p->opr.op[0]);
	int a = getRunTimeLon(globalRunTimeValue);

	if(b > a){
		setRunTimeBoo(globalRunTimeValue, 1);

	}else{
		
		setRunTimeBoo(globalRunTimeValue, 0);
	}
}


void geNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	int b = getRunTimeLon(globalRunTimeValue);

	ex(p->opr.op[0]);
	int a = getRunTimeLon(globalRunTimeValue);

	if(b <= a){
		setRunTimeBoo(globalRunTimeValue, 1);

	}else{
		
		setRunTimeBoo(globalRunTimeValue, 0);
	}
}


void leNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	int b = getRunTimeLon(globalRunTimeValue);

	ex(p->opr.op[0]);
	int a = getRunTimeLon(globalRunTimeValue);

	if(b >= a){
		setRunTimeBoo(globalRunTimeValue, 1);

	}else{
		
		setRunTimeBoo(globalRunTimeValue, 0);
	}
}


void neNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	int b = getRunTimeLon(globalRunTimeValue);

	ex(p->opr.op[0]);
	int a = getRunTimeLon(globalRunTimeValue);

	if(b != a){
		setRunTimeBoo(globalRunTimeValue, 1);

	}else{
		
		setRunTimeBoo(globalRunTimeValue, 0);
	}
	
}


void eqNodeVisit(nodeType *p){
	ex(p->opr.op[1]);
	int b = getRunTimeLon(globalRunTimeValue);

	ex(p->opr.op[0]);
	int a = getRunTimeLon(globalRunTimeValue);

	if(b == a){
		setRunTimeBoo(globalRunTimeValue, 1);

	}else{
		
		setRunTimeBoo(globalRunTimeValue, 0);
	}

}



void ex(nodeType *p) {

    if (!p){ 
		
	}
    else{
		if(p->type == typeIdentifierNode){
			idNodeVisit(p);
		}
		if(p->type == typeIntegerValue){
			intNodeVisit(p);
		}
		if(p->type == typeStringValue){
			stringNodeVisit(p);
		}
		if(p->type == typeDoubleValue){
			douNodeVisit(p);
		}
		if(p->type == typeOpr){
			if(p->opr.oper == INTDEFNO){
				intAssignVisit(p);
			}
			if(p->opr.oper == STRCAT){
				strCatVisit(p);
			}
			if(p->opr.oper == WHILE) {
				whileNodeVisit(p);
			}
			if(p->opr.oper == IF){
				ifNodeVisit(p);
			}
			if(p->opr.oper == PRINT){     	 printNodeVisit(p);}
			if(p->opr.oper == PRINTLN){      printlnNodeVisit(p);}
			if(p->opr.oper == SEMCOL){       semcolNodeVisit(p);}
			if(p->opr.oper == INTDEF){
				intDefNodeVisit(p);
			}
			if(p->opr.oper == SHODEF){
				shoDefNodeVisit(p);
			}
			if(p->opr.oper == CHADEF){
				chaDefNodeVisit(p);
			}
			if(p->opr.oper == FLODEF){
				floDefNodeVisit(p);
			}
		
			if(p->opr.oper == STRDEF){
				strDefNodeVisit(p);
			}
			if(p->opr.oper == LONDEF){
				lonDefNodeVisit(p);
			}


			
			if(p->opr.oper == UMINUS){    uminusNodeVisit(p);}
			if(p->opr.oper == '+'){       plusNodeVisit(p);}
			if(p->opr.oper == '-'){       minusNodeVisit(p);}
			if(p->opr.oper == '*'){       multiNodeVisit(p);}
			if(p->opr.oper == '/'){       divNodeVisit(p);}
		
			if(p->opr.oper == '<'){       lessThanNodeVisit(p);}
			if(p->opr.oper == '>'){       greaterThanNodeVisit(p);}
			
			if(p->opr.oper == GE){        geNodeVisit(p);}
			if(p->opr.oper == LE){        leNodeVisit(p);}
			if(p->opr.oper == NE){        neNodeVisit(p);}
			if(p->opr.oper == EQ){        eqNodeVisit(p);}
			}
		}

}

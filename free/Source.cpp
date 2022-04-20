#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
// ct+1番目の指定した文字列の先頭アドレスを返す
char* split(char* subject, char* devide, int ct);
// 数値を文字列に変換
char* tostring(int number);
//　文字列検索
char* search(char* subject, char* devide);
//　文字数検索
int ctchar(char* subject, char* specian);
//　指定文字の削除
char* eliminate(char* subject, char specian);
//　式を作る
typedef struct TREE
{
	TREE* left, * right;
	char* value;
};

//　演算子検出
char* Division(char* st, char mark);
//　ツリー構造作成
void descent(TREE* parent,char sign);
//　両端の括弧の除去
char* trimbrackets(char* st);
//　ツリーへのトラッキング
char* tracking(TREE* parent, char* st);
//　逆ポーランド記法
char* formularise();
//　行列式の入力
char*** dataget();

char*** calculate(char* form);
//　加減算処理
char*** addtion(char*** formula1, char*** formula2, int code);
//　積の計算
char*** production(char*** formula1, char*** formula2 );
//char* typing(void);
int main(void)
{
	char *form,***data;
	int ct1, ct2;
	while (0)
	{
		printf("Type a form\n" );
		form = formularise();
		printf("%s\n", form);
	}
	form = formularise();
	printf("%s\n", form);

	data = calculate(form);

	for (ct1 = 0; data[ct1] != NULL; ct1++)
	{
		for (ct2 = 0; data[ct1][ct2] != NULL; ct2++)
		{
			printf("%s ", data[ct1][ct2]);
		}
		printf("\n");
	}
	while (0)
	{
		data = dataget();
		for (ct1 = 0; data[ct1][0] != NULL; ct1++)
		{
			for (ct2 = 0; data[ct1][ct2] != NULL; ct2++)
			{
				printf("%s ", data[ct1][ct2]);
			}
			printf("\n");
		}
	}
	return 0;
}
char*** addtion(char*** formula1, char*** formula2, int code)
{
	char*** tentative, *** result;
	int row,column,many;
	int mater;
	int ctr,ctc;
	tentative = formula1;
	many = 0;
	for (row = 0; formula1[row][0] != NULL; row++);
	for (column = 0; formula1[0][column] != NULL; column++);

	result = (char***)malloc(sizeof(char*)* (row+1)* (column + 1));
	for (ctr = 0; ctr < row; ctr++)
	{
		result[ctr] = (char**)malloc(sizeof(char*) * (column + 1));
		for (ctc = 0; ctc < column; ctc++)
		{
			mater =
				atoi(formula1[ctr][ctc]) + atoi(formula2[ctr][ctc]) * code;
			result[ctr][ctc] = tostring(mater);
			//strcpy(result[ctr][ctc], copy);
		}
		result[ctr][column] = NULL;
	}
	result[row] = NULL;

	return result;
}
//　１つめの行列のrow 　　２つ目の行列のcolumn　
char*** production(char*** formula1, char*** formula2)
{
	char*** tentative1, *** tentative2,***result;
	int row, column,same;
	int mater;
	int ctr1, ctc1,ct;
	tentative1 = formula1;
	tentative2 = formula2;

	for (same = 0; tentative1[0][same] != NULL; same++);
	for (row = 0; tentative1[row][0] != NULL; row++);
	for (column = 0; tentative2[0][column] != NULL; column++);

	result = (char***)malloc(sizeof(char*) * (row + 1) * (column + 1));
	for (ctr1 = 0; ctr1 < row; ctr1++)
	{
		result[ctr1] = (char**)malloc(sizeof(char*) * (column + 1));
		for (ctc1 = 0; ctc1 < column; ctc1++)
		{
			mater = 0;
			for (ct = 0; ct < same; ct++)
			{
				mater +=
					atoi(formula1[ctr1][ct]) * atoi(formula2[ct][ctc1]);
			}
			result[ctr1][ctc1] = tostring(mater);

		}
		result[ctr1][ctc1] = NULL;
	}
	result[ctr1] = NULL;

	return result;
}
char*** dataget()
{
	char sequence[400], * sepa,***data; 
	char* alter;
	int row, culct, ct, ct2;

	struct CELL
	{
		//　値
		char* value;
		//　次の列のアドレス
		CELL* following;
	};
	struct ROW
	{
		//　列の数
		int column;
		//　先頭アドレス
		CELL *heads;
		//　次の行のアドレス
		ROW* next;
	};

	ROW * Queue, *head,* inspect;
	CELL* cell,*train;

	//printf("%d", sizeof(char));
	Queue = (ROW*)malloc(sizeof(ROW));
	head = Queue;

	sepa = (char*)malloc(sizeof(char) * 2);
	strcpy(sepa, " ");

	inspect = NULL;
	train = NULL;
	row = 1;
	while (1)
	{

		fgets(sequence, 300, stdin);
		//　endコマンドで入力終了
		if (strcmp(sequence, "\n") == 0)
		{
			inspect->next = NULL;
			break;
		}

		//　要素数の格納
		//　	コンマの数をカウントして列の数を数える
		Queue->column = ctchar(sequence, sepa) + 1;

		cell = (CELL*)malloc(sizeof(CELL));
		Queue->heads = cell;
		alter = sequence - 1;

		for (ct = 0; ct < Queue->column; ct++)
		{
			//　ct列目の要素数+1
			//　２つのスペースの間のアドレスを算出
			if (split(sequence, sepa, ct) != NULL)
			{
				culct = split(sequence, sepa, ct) - alter;
			}
			else
			{
				culct = strlen(alter)-1;
			}
			//　領域確保
			cell->value = (char*)malloc(sizeof(char) * culct);
			//　要素の代入（ナル文字込み）
			memcpy(cell->value, alter + 1, culct);
			*((cell->value) + culct - 1) = '\0';
			//　スペースを\0に変える
			train = cell;
			cell->following = (CELL*)malloc(sizeof(CELL));
			cell = cell->following;

			alter = split(sequence, sepa, ct);
		}
		train->following = NULL;
		inspect = Queue;
		Queue->next = (ROW*)malloc(sizeof(ROW));
		Queue = Queue->next;
		row++;
	}

	culct = head->column + 1;
	data = (char***)malloc(sizeof(char*)*(row+1)* (culct+1));
	ct = 0;
	for (inspect = head; inspect != NULL; inspect = inspect->next )
	{
		//　２週目でエラー
		cell = inspect->heads;
		//　0じゃないといけない
		//printf("%d", inspect - cell);
		data[ct] = (char**)malloc(sizeof(char*) * (culct + 1));
		for (ct2 = 0; ct2 < inspect->column ; ct2++)
		{
			data[ct][ct2] =  cell->value;
			cell = cell->following;
		}
		data[ct][ct2] = NULL;
		printf("\n");
		ct++;
	}
	data[ct] = (char**)malloc(sizeof(char*));
	data[ct][0] = NULL;
	return data;
}
int ctchar(char* subject, char* specian)
{
	int  pt = 0, many;
	//　検索文字の個数 many
	many = strlen(specian);

	while (1)
	{
		subject = search(subject, specian);
		if (subject == NULL)break;
		subject += many;
		pt++;
	}
	return pt;
}
char* split(char* subject, char* devide, int ct)
{
	int  pt = 0, many;
	//　検索文字の個数 many
	many = strlen(devide);

	while (1)
	{
		subject = search(subject, devide);
		if (subject == NULL)break;
		pt++;
		if (pt > ct)return subject;
		subject += many;
	}
	return NULL;
}
char* search(char* subject, char* devide)
{

	int ct1 = 0, ct2 = 0, initial = 0, many;
	bool sign = true;
	char* pointa;
	many = strlen(devide);
	pointa = subject;
	while (1)
	{
		if (*pointa == '\0')break;
		if (*pointa == '\n')break;
		// 文字列判定
		if (*pointa == *(devide+ct2) )
		{
			//　あってたらct2を1増やす
			ct2++;
			//　ct2が検索文字の文字数以上で終了
			if (ct2 >= many)
			{
				return pointa - many + 1;
			}
			if (sign)
			{
				//　検索文字の最初の文字があればinitialに記録
				initial++;
				if ((*pointa == *devide) && (ct2 != 0))
				{
					sign = false;
				}
			}
		}
		//　あってなければinitialから再検索
		else
		{
			ct2 = 0;
			sign = true;
			ct1 = initial;
		}
		pointa++;
	}
	return NULL;
}
char* formularise()
{
	char* sequence, * form;
	char *alter,change,* tail;
	int length;
	sequence = (char*)malloc(sizeof(char) * 301);
	printf("Please enter queue!!\n");
	fgets(sequence, 300, stdin);
	sequence = eliminate(sequence, ' ');
	length = strlen(sequence);
	*(sequence + length - 1) = '\0';
	length--;
	TREE* route;
	route = (TREE*)malloc(sizeof(TREE));
	route->value = sequence;
	descent(route, '+');

	form = (char*)malloc(sizeof(char)* length);
	tracking(route, form);
	length = strlen(form);
	alter = form;
/*	for (tail = form + length - 1; alter < tail; tail--)
	{
		change = *alter;
		*alter = *tail;
		*tail = change;
		alter++;
	}*/
	return form;
}

char* tracking(TREE* parent,char *st)
{
	char* next;
	if (parent == NULL)
	{
		return st;
	}
	st = tracking(parent->left, st);
	st = tracking(parent->right, st);
	*st = *parent->value;
	*(st+1) = '\0';
	return st+1;
}
void descent(TREE* parent, char sign)
{
	char* mark;
	int LeftLength, RightLength;
	char brakets[] = "(\0";
	TREE* Left, * Right;
	Left = (TREE*)malloc(sizeof(TREE));
	Right = (TREE*)malloc(sizeof(TREE));
	if (parent == NULL)return;

	mark = Division(parent->value, sign);
	if (mark != NULL)
	{
		LeftLength = strlen(parent->value) - strlen(mark);
		parent->left = Left;
		if (LeftLength == 0)
		{
			parent->left = NULL;
		}
		else
		{
			Left->value =
				(char*)malloc(sizeof(char) * (LeftLength + 1));
			memcpy(Left->value, parent->value, LeftLength);
			*(Left->value + LeftLength) = '\0';
			//Left->value = trimbrackets(Left->value);
		}

		RightLength = strlen(parent->value) - LeftLength;
		parent->right = Right;

		if (RightLength == 0)
		{
			parent->right = NULL;
		}
		else
		{
			Right->value =
				(char*)malloc(sizeof(char) * (RightLength + 1));
			memcpy(Right->value, mark + 1, RightLength);
			*(Right->value + RightLength) = '\0';
			//Right->value = trimbrackets(Right->value);

		}
		parent->value = (char*)malloc(sizeof(char)*2);
		*(parent->value) = *mark;
		*((parent->value) + 1) = '\0';

		descent(Left, sign);
		descent(Right, sign);

	}
	else
	{
		if (sign == '+')
		{
			descent(parent, '*');
		}
		else
		{
			if ( ctchar(parent->value,brakets) == 0)
			{
				parent->right = NULL;
				parent->left = NULL;
				return;
			}
			else
			{
				parent->value = trimbrackets(parent->value);
				descent(parent, '+');
			}
		}
	}
	return;
}
char* Division(char* st, char mark)
{
	int deepct;
	deepct = 0;
	while (*st != '\0')
	{
		if (*st == '(')
		{
			deepct++;
		}
		else if (*st == ')')
		{
			deepct--;
		}
		else if (deepct == 0)
		{
			if (mark == '+')
			{
				if (*st == '+' || *st == '-')
				{
					return st;
				}
			}
			else if (mark == '*')
			{
				if (*st == '*')
				{
					return st;
				}
			}
		}
		else
		{
		}
		st++;
	}
	return NULL;
}
char* trimbrackets(char* st)
{
	int length, sign, deep;
	char* head, * tail;

	length = strlen(st);
	head = st;
	sign = 0;
	tail = st + length - 1;

	if ((*head == '(') && (*tail == ')'))
	{
		st++;
		deep = 1;
		while (st < tail)
		{
			if (*st == '(')
			{
				deep++;
			}
			else if (*st == ')')
			{
				deep--;
				if (deep == 0)return head;
			}
			st++;
		}
		*tail = '\0';
		head++;
	}
	return head;
}
char* eliminate(char* subject, char specian)
{
	char* clear,*str;
	int domain,ct1,ct2;
	str = (char*)malloc(sizeof(char) * 2);
	*str = specian;
	*(++str) = '\0';
	domain = strlen(subject)-ctchar(subject, str)+1;
	clear = (char*)malloc(sizeof(char) * domain);
	ct2 = 0;
	for (ct1 = 0; ct1 < strlen(subject); ct1++)
	{
		if (*(subject + ct1) != specian)
		{
			*(clear + ct2) = *(subject + ct1);
			ct2++;
		}
	}
	*(clear + ct2) = '\0';
	return clear;
}
char*** calculate(char* form)
{
	char *current;
	char***data1, *** data2;
	int length;
	typedef struct STUCK
	{
		char mark;
		char* name;
		char*** result;
		//int** mater;
		STUCK* next;
		STUCK* before;
	};
	STUCK* stuck,*head,*tentative;
	length = strlen(form);
	stuck = (STUCK*)malloc(sizeof(STUCK));
	head = stuck;
	stuck->before = NULL;
	for (current = form; *current != '\0'; current++)
	{
		if( (('a' <= *current) && ('z' <= *current))||
			(('A' <= *current) && ('Z' <= *current)) )
		{
			//*(stuck->name) = *current;
			printf("Type a data\n");
			data1 = dataget();
			stuck->result = data1;
			stuck->mark = *current;
			stuck->next = (STUCK*)malloc(sizeof(STUCK));
			tentative = stuck;
			stuck = stuck->next;
			stuck->before = tentative;
		}
		else if( *current == '+'|| *current == '-' || *current == '*' )
		{
			stuck = stuck->before;
			data2 = stuck->result;

			stuck = stuck->before;
			data1 = stuck->result;
			switch (*current)
			{
				case '+':
					stuck->result = addtion(data1, data2, 1);
					break;
				case '-':
					stuck->result = addtion(data1, data2, -1);
					break;
				case '*':
					stuck->result = production(data1, data2);
					break;

				default:

					break;
			}
			tentative = stuck->next;
			tentative = tentative->next;
			free(stuck->next);
			stuck->next = tentative;
			tentative->before = stuck;

		}
		else
		{

		}
		stuck->next = NULL;
	}

	return head->result;
}
char* tostring(int number)
{
	char* string, * head;
	int ct, ct1, num;
	//　マイナスへの対応
	if (number < 0)
	{
		ct = int(log10(double(-number))) + 2;
		string = (char*)malloc(sizeof(char)*ct);
		head = string;
		number = -number;
		*string = '-';
		string++;
	}
	else
	{
		if (number == 0)
		{
			ct = 2;
		}
		else
		{
			ct = int(log10(double(number))) + 2;
		}
		string = (char*)malloc(sizeof(char) * ct);
		head = string;
	}

	for (ct1 = ct - 2; ct1 >= 0; ct1--)
	{
		num = int(pow(10.0, double(ct1)));
		*string = number / int(pow(10.0, double(ct1))) + '0';
		number %= int(pow(10.0, double(ct1)));
		string++;
	}
	*string = '\0';
	return head;
}

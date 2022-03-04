#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>
#include <time.h>

#define MAX_COUNT 100
#define SUBJECT 3 // 과목수

// 성적프로그램 구조체 정의
struct STUDENT_INFO{
 char name[5];
 int no;
 int gender;
 int c;
 int java;
 int html;
 int total;
 double avr;
 char grade;
};

typedef struct STUDENT_INFO STUDENT;

void input_score(STUDENT *student); //성적입력 함수 선언
char grade_check(double avr); //성적 등급 함수 선언
void print_score(STUDENT *student, int count); //성적출력 함수 선언
void search_score(STUDENT *student); // 성적검색 함수 선언
void delete_score(student); //성적삭제 함수 선언
void update_score(STUDENT *student); //성적수정 함수 선언
void insert_score(STUDENT *student); //성적추가 함수 선언
void sort_score(STUDENT *student); //성적정렬 함수 선언


int total_count = 0;

int main()
{
    int menu = 0;
    int flag = 0;
    STUDENT student[MAX_COUNT];

    printf("성적관리 할 학생수 입력 :");
    scanf("%d",&total_count);

    while(!flag){
        system("cls");
        fflush(stdin);

        printf("1 성적PG 입력(자동) \n");
        printf("2 성적PG 출력 \n");
        printf("3 성적PG 검색 \n");
        printf("4 성적PG 삭제 \n");
        printf("5 성적PG 수정 \n");
        printf("6 성적PG 추가(수동) \n");
        printf("7 성적PG 정렬(오름차순,내림차순) \n");
        printf("8 성적PG 종료 \n");

        printf("메뉴를 선택하시오 : ");
        scanf("%d",&menu);

        switch(menu){
            case 1 :
                // STUDENT student[MAX_COUNT]; 구조체 배열명 (STUDENT *)
                input_score(student);
                printf("성적프로그램 입력완료(메뉴로 갈려면 엔터입력)");
                getchar();
                getchar();
                break;
            case 2 :
                print_score(student, total_count);
                printf("성적프로그램을 출력완료(메뉴로 갈려면 엔터입력)");
                getchar();
                getchar();
                break;
            case 3 :
                search_score(student);
                printf("성적프로그램을 검색완료(메뉴로 갈려면 엔터입력)");
                getchar();
                getchar();
                break;
            case 4 :
                delete_score(student);
                printf("성적프로그램을 삭제(메뉴로 갈려면 엔터입력)");
                getchar();
                getchar();
                break;
            case 5 :
                update_score(student);
                printf("성적프로그램을 수정하였습니다.");
                getchar();
                getchar();
                break;
            case 6 :
                insert_score(student);
                printf("성적프로그램을 추가하였습니다.");
                getchar();
                getchar();
                break;
            case 7 :
                sort_score(student);
                printf("성적프로그램을 정렬하였습니다.");
                getchar();
                getchar();
                break;
            case 8 :
                printf("성적프로그램을 종료를 선택하였습니다.\n");
                flag = 1;
                break;
            default :
                printf("번호를 다시 선택하세요 \n");
                break;
        } // end of switch

    } // end of while
    printf("성적프로그램을 종료합니다.\n");
return 0;
}

// STUDENT student[MAX_COUNT]; 구조체 배열명 (STUDENT (*~~~))
void input_score(STUDENT *student){
    int i = 0;
    //랜덤 초기화 진행
    srand(time(NULL));
    //전체인원별 자동 입력 진행
    for(i=0;i<total_count;i++){
        //이름 3글자 설정(대문자로 자동입력)
        student[i].name[0] = rand()%(25-0+1)+0+'A';
        student[i].name[1] = rand()%(25-0+1)+0+'A';
        student[i].name[2] = rand()%(25-0+1)+0+'A';
        student[i].name[3] = 0;

        //번호 1~1000 자동입력
        student[i].no = rand()%(1000-1+1)+1;
        //성별 0 :여, 1 :남
        student[i].gender = rand()%(1-0+1)+0;
        //점수 0~100
        student[i].c = rand()%(100-0+1)+0;
        student[i].java = rand()%(100-0+1)+0;
        student[i].html = rand()%(100-0+1)+0;
        //총점계산
        student[i].total = student[i].c +student[i].java + student[i].html;
        //평균계산
        student[i].avr = student[i].total / (double)SUBJECT;
        //등급계산 90점이상:A 80점이상:B 70점이상:C 60점이상:D 60점미만:F
        student[i].grade = grade_check(student[i].avr);
    }
    return;
}

//등급계산 90점이상:A 80점이상:B 70점이상:C 60점이상:D 60점미만:F
char grade_check(double avr){
    char grade = 0;

    if(avr >= 90.0){
        grade = 'A';
    }else if(avr >= 80.0){
        grade = 'B';
    }else if(avr >= 70.0){
        grade = 'C';
    }else if(avr >= 60.0){
        grade = 'D';
    }else {
        grade = 'F';
    }
    return grade;
}

void print_score(STUDENT *student, int count){
    int i = 0;
    //check study
    for(i=0; i<count; i++){
        printf("%4d %6s %5d %3s %3d %3d %3d %5d %6.2lf %5c \n",
               i+1, &student[i].name[0], student[i].no, (student[i].gender)==1?"남":"여",
               student[i].c, student[i].java, student[i].html, student[i].total, student[i].avr,student[i].grade );
    }
    return;
}

void search_score(STUDENT *student){
    char name[5]={0,};
    int i=0;
    int search_flag=0;

    printf("찾는 학생이름입력(3글자입력) : ");
    scanf("%s",&name[0]);

    //문자열비교 대소문자 구분하지 않음 int strcmpi(const char *string1, const char *string2);
    for(i=0;i<total_count;i++){
        if(strcmpi(&name[0],&student[i].name[0])==0){
            print_score(&student[i],1);
            search_flag=1;
        }
    }

    if(search_flag==0){
        printf("%s 이름이 없습니다.\n",&name[0]);
    }
    return;
}


void delete_score(STUDENT *student){
    char name[5]={0,};
    int i=0;
    int delete_flag=0;

    printf("삭제할 학생이름입력(3글자입력) : ");
    scanf("%s",&name[0]);

    //문자열비교 대소문자 구분하지 않음 int strcmpi(const char *string1, const char *string2);
    for(i=0;i<total_count;i++){
        if(strcmpi(&name[0],&student[i].name[0])==0){
            student[i].name[0]='_';
            student[i].name[1]='_';
            student[i].name[2]='_';
            student[i].no=0;
            student[i].gender=0;
            student[i].c=0;
            student[i].java=0;
            student[i].html=0;
            student[i].total=0;
            student[i].avr=0.0;
            student[i].grade='_';
            delete_flag=1;
        }
    }

    if(delete_flag==0){
        printf("삭제할 %s 이름이 없습니다.\n",&name[0]);
    }
    return;
}

void update_score(STUDENT *student){
    char name[5]={0,};
    int i=0;
    int update_flag=0;

    printf("수정할 학생이름입력(3글자입력) : ");
    scanf("%s",&name[0]);

    //문자열비교 대소문자 구분하지 않음 int strcmpi(const char *string1, const char *string2);
    for(i=0;i<total_count;i++){
        if(strcmpi(&name[0],&student[i].name[0])==0){
            print_score(&student[i], 1);
            printf("수정할 점수 C 입력(0~100) ");
            scanf("%d",&student[i].c);
            printf("수정할 점수 java 입력(0~100) ");
            scanf("%d",&student[i].java);
            printf("수정할 점수 html 입력(0~100) ");
            scanf("%d",&student[i].html);
            student[i].total=student[i].c+student[i].java+student[i].html;
            student[i].avr=student[i].total/(double)SUBJECT;
            student[i].grade=grade_check(student[i].avr);
            update_flag=1;
        }
    }

    if(update_flag==0){
        printf("수정할 %s 이름이 없습니다.\n",&name[0]);
    }

return;
}

void insert_score(STUDENT *student){

        printf("추가할 이름 입력(3글자) ");
        scanf("%s",&student[total_count].name[0]);
        printf("추가할 번호 입력(1~1000) ");
        scanf("%d",&student[total_count].no);
        printf("추가할 성별 입력(여:0 남:1) ");
        scanf("%d",&student[total_count].gender);
        printf("추가할 점수 C 입력(0~100) ");
        scanf("%d",&student[total_count].c);
        printf("추가할 점수 java 입력(0~100) ");
        scanf("%d",&student[total_count].java);
        printf("추가할 점수 html 입력(0~100) ");
        scanf("%d",&student[total_count].html);
        student[total_count].total=student[total_count].c+student[total_count].java+student[total_count].html;
        student[total_count].avr=student[total_count].total/(double)SUBJECT;
        student[total_count].grade=grade_check(student[total_count].avr);

        total_count++;
}


void sort_score(STUDENT *student){
    int sort_type=0;
    int i=0, j=0;
    STUDENT copy_student[total_count];
    STUDENT student_buffer;

    printf("오름차순: 1, 내림차순: 2 : ");
    scanf("%d",&sort_type);

    //원본 -> 사본으로 구조체 배열 복사  void *memcpy(void *_Dst, void const *_Src, size_t _Size);
    for(i=0;i<total_count;i++){
        memcpy(&copy_student[i], &student[i], sizeof(STUDENT));
    }

    switch(sort_type){
        case 1:
            //오름차순정렬
            for(i=0;i<total_count-1;i++){
                for(j=i+1;j<total_count;j++){
                    if(copy_student[i].total > copy_student[j].total){
                        memcpy(&student_buffer,&copy_student[i], sizeof(STUDENT));
                        memcpy(&copy_student[i],&copy_student[j], sizeof(STUDENT));
                        memcpy(&copy_student[j],&student_buffer, sizeof(STUDENT));
                    }
                }
            }//end of for
            print_score(copy_student, total_count);
            break;
        case 2:
            //내림차순정렬
           for(i=0;i<total_count-1;i++){
                for(j=i+1;j<total_count;j++){
                    if(copy_student[i].total < copy_student[j].total){
                        memcpy(&student_buffer,&copy_student[i], sizeof(STUDENT));
                        memcpy(&copy_student[i],&copy_student[j], sizeof(STUDENT));
                        memcpy(&copy_student[j],&student_buffer, sizeof(STUDENT));
                    }
                }
            }//end of for
            print_score(copy_student, total_count);

            break;
        default: puts("잘못 선택하셨습니다.");
    }

    return;
}

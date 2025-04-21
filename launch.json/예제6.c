// 발표용 주석: 이 코드는 HTML 태그의 종료 태그를 자동으로 추가하는 프로그램입니다. 입력된 HTML 코드를 읽고, 누락된 종료 태그를 추가해 완전한 HTML을 출력합니다.

#define _CRT_SECURE_NO_WARNINGS  // 발표용 주석: Visual Studio에서 보안 경고를 비활성화합니다. (strncpy, strcpy 등의 함수 사용 시 경고 억제)

#include <stdio.h>   // 발표용 주석: 표준 입출력 함수를 사용합니다. (fgets, printf 등)
#include <string.h>  // 발표용 주석: 문자열 처리 함수를 사용합니다. (strchr, strcmp 등)
#include <stdlib.h>  // 발표용 주석: 동적 메모리 할당 함수를 사용합니다. (strdup 등)
#include <ctype.h>   // 발표용 주석: 문자 판별 함수를 사용합니다. (isspace 등)

// 발표용 주석: 상수 정의 - 프로그램의 한계를 설정합니다.
#define MAX_LINES 1000      // 최대 줄 수: 입력 줄의 최대 개수
#define MAX_LINE_LEN 2048   // 한 줄의 최대 길이: 한 줄에 들어갈 수 있는 문자 수
#define MAX_TAGS 1000       // 최대 태그 수: 스택에 저장할 수 있는 태그 개수
#define MAX_TAG_LEN 256     // 태그 이름 최대 길이: 태그 이름의 최대 문자 수

// 발표용 주석: 태그 이름 추출 함수 - HTML 태그에서 태그 이름만 추출합니다.
// 예: "<div>" 또는 "</div>"에서 "div"를 추출
void extract_tagname(const char* tag, char* tagname, int is_closing) {
    int i = is_closing ? 2 : 1;  // 발표용 주석: 닫는 태그면 2부터, 여는 태그면 1부터 시작합니다.
    int j = 0;
    // 발표용 주석: 태그 이름 추출 - 공백, '>', '/'를 만나기 전까지 복사
    while (tag[i] && !isspace((unsigned char)tag[i]) && tag[i] != '>' && tag[i] != '/' && j < MAX_TAG_LEN - 1) {
        tagname[j++] = tag[i++];
    }
    tagname[j] = '\0';  // 발표용 주석: 태그 이름 끝에 널 문자를 추가
}

int main() {
    // 발표용 주석: 변수 선언 - 입력과 태그 관리를 위한 변수들
    char line[MAX_LINE_LEN];                   // 한 줄 입력을 저장
    char* lines[MAX_LINES];                    // 입력 줄을 저장할 배열
    char stack[MAX_TAGS][MAX_TAG_LEN];         // 열린 태그를 저장할 스택
    int top = 0, line_count = 0;               // 스택 위치와 줄 개수

    // 발표용 주석: 1단계 - 입력 처리: 한 줄씩 읽어 처리
    while (fgets(line, sizeof(line), stdin)) {
        int stop = 0;  // 발표용 주석: 입력 종료 여부를 나타내는 플래그
        int len = strlen(line);
        // 발표용 주석: 줄 끝의 개행 문자 제거
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        // 발표용 주석: 줄 끝에 '.'가 있으면 입력 종료
        if (len > 0 && line[len - 1] == '.') {
            stop = 1;
            line[len - 1] = '\0';  // '.' 제거
        }

        // 발표용 주석: 입력 줄을 메모리에 저장
        lines[line_count] = _strdup(line);

        // 발표용 주석: 2단계 - 태그 파싱: 줄에서 태그를 찾아 처리
        char* p = line;
        while ((p = strchr(p, '<')) != NULL) {  // '<'로 시작하는 태그 찾기
            char* gt = strchr(p, '>');  // 대응되는 '>' 찾기
            if (!gt) break;  // '>'가 없으면 태그 처리 중단

            // 발표용 주석: 태그를 추출하여 저장
            int taglen = gt - p + 1;
            char tag[MAX_TAG_LEN];
            strncpy(tag, p, taglen);
            tag[taglen] = '\0';

            char tagname[MAX_TAG_LEN] = { 0 };  // 태그 이름 저장용
            if (tag[1] == '/') {  // 발표용 주석: 닫는 태그 처리 (예: </div>)
                extract_tagname(tag, tagname, 1);  // 태그 이름 추출
                // 스택에서 동일한 태그 제거
                if (top > 0 && strcmp(stack[top - 1], tagname) == 0) {
                    
                    top--;
                }
            }
            else {  // 발표용 주석: 여는 태그 처리 (예: <div>)
                if (taglen < 3 || tag[taglen - 2] != '/') {  // self-closing 태그가 아닌 경우
                    extract_tagname(tag, tagname, 0);  // 태그 이름 추출
                    // 스택에 태그 추가
                    if (top < MAX_TAGS && strlen(tagname) > 0) {
                        strcpy(stack[top++], tagname);
                    }
                }
            }
            p = gt + 1;  // 다음 태그로 이동
        }

        line_count++;  // 줄 개수 증가
        // 발표용 주석: 입력 종료 조건 확인
        if (stop || line_count >= MAX_LINES) break;
    }

    // 발표용 주석: 3단계 - 출력: 처리된 줄 출력
    for (int i = 0; i < line_count; i++) {
        printf("%s", lines[i]);  // 원본 줄 출력
        free(lines[i]);  // 메모리 해제
    }

    // 발표용 주석: 4단계 - 남은 태그 닫기: 스택에 남은 태그를 닫음
    while (top > 0) {
        printf("</%s>", stack[--top]);
    }

    printf("\n");  // 출력 마무리
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <curl/curl.h>

//-------------------------------------------------------------------------------------------------------

void encontrar_dnd(const char* ip, int estado, char* request, char* query) {
  int nparam = -1;
  char nfich[512], nurl[512];
#ifdef DUOCOM_WIN32
  sprintf(nfich, "%s\\ciscodnd", getenv("TEMP"));
#else
  sprintf(nfich, "/tmp/ciscodnd");
#endif
  
  sprintf(nurl, "http://%s", ip);
  FILE* fd = fopen(nfich, "w");

  CURL* curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, nurl);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
    CURLcode res = curl_easy_perform(curl);
    printf("res = %d\n", res);
    curl_easy_cleanup(curl);
    fclose(fd);

    fd = fopen(nfich, "r");
    if (fd != NULL) {
      while (!feof(fd)) {
	char linea[4096];
	fgets(linea, sizeof(linea), fd);
	if (!feof(fd)) {
	  char* idx;
	  // DND Setting:&nbsp;&nbsp;&nbsp;&nbsp;<td><select class="inputw" name="9133">
	  if ((idx = strstr(linea, "DND Setting:")) != NULL) {
	    idx = strstr(idx, "select");
	    if (idx == NULL)
	      continue;
	    idx = strstr(idx, "name=");
	    if (idx == NULL)
	      continue;
	    idx += 6;
	    nparam = atoi(idx);
	    break;
	  }
	  else if ((idx = strstr(linea, "form")) != NULL) {
	    idx = strstr(idx, "action=");
	    if (idx == NULL)
	      continue;
	    idx += 8;
	    char* idx_end;
	    idx_end = strstr(idx,"\"");
		size_t len = idx_end-idx;
		char* res = (char*)malloc(sizeof(char)*(len+1));
		strncpy(res, idx, len);
		res[len] = '\0';
		sprintf(request, "%s", res);
		free(res);
	  }
	}
      }
      fclose(fd);
    }

    remove(nfich);
  }
  sprintf(query, "%d=%d", nparam, estado);
}

//-------------------------------------------------------------------------------------------------------

void mandar_dnd(const char* ip, char* request, char* query) {
  char nfich[512], nurl[512];
  sprintf(nurl, "http://%s/%s", ip, request);
  
  CURL* curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, nurl);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query);
#ifdef DUOCOM_WIN32
  sprintf(nfich, "%s\\ciscodnd", getenv("TEMP"));
#else
  sprintf(nfich, "/tmp/ciscodnd");
#endif
  FILE* fd = fopen(nfich, "w");
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
    
    CURLcode res = curl_easy_perform(curl);
    fclose(fd);
    printf("res = %d\n", res);
    curl_easy_cleanup(curl);
  }
}

//-------------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {
  const char* uso = "\nUso: %s ip_address dnd/-dnd\n\n";
  if (argc != 3) {
    printf(uso, argv[0]);
    return -1;
  }

  char* ip = argv[1];
  char* orden = argv[2];

  if (strcmp(orden, "-dnd") == 0) {
    char* request = (char*)malloc(512);
    char* query = (char*)malloc(512);
    encontrar_dnd(ip, 0, request, query);
    mandar_dnd(ip, request, query);
    free(request);
    free(query);
  }
  else if (strcmp(orden, "dnd") == 0) {
    char* request = (char*)malloc(512);
    char* query = (char*)malloc(512);
    encontrar_dnd(ip, 1, request, query);
    mandar_dnd(ip, request, query);
    free(request);
    free(query);
  }
  else {
    printf(uso, argv[0]);    
  }

  return 0;
}

//-------------------------------------------------------------------------------------------------------

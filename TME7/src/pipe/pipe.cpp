#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

void print_tab2(char **tab)
{
    for (int i = 0; tab[i] != nullptr; ++i)
    {
        printf("%s ", tab[i]);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s cmd1 ... | cmd2 ...\n", argv[0]);
        return 1;
    }

    char **cmd1 = argv + 1;
    char **cmd2 = nullptr;

    for (int i = 1; i < argc - 1; ++i)
    {
        // printf(":%s: ", argv[i]);

        if (argv[i][0] == '|' && argv[i][1] == '\0')
        {
            argv[i] = nullptr;
            cmd2 = argv + i + 1;
        }
    }

    if (cmd2 == nullptr)
    {
        fprintf(stderr, "No pipe found");
        return 1;
    }

    // print_tab2(cmd1);
    // print_tab2(cmd2);

    int fds[2];
    if (pipe(fds))
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    { // Fils 1
        close(fds[0]);
        if (dup2(fds[1], STDOUT_FILENO) == -1)
        { // Rediriger stdout vers le pipe
            perror("dup2");
            exit(1);
        }
        execv(cmd1[0], cmd1);
        perror("execv"); // En cas d'échec
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid2 == 0)
    { // Fils 2
        close(fds[1]);
        if (dup2(fds[0], STDIN_FILENO))
        {
            perror("dup2");
            exit(1);
        }

        execv(cmd2[0], cmd2);
        perror("execv"); // En cas d'échec
        exit(1);
    }

    close(fds[0]);
    close(fds[1]);


    // Attendre les processus enfants
    waitpid(pid, nullptr, 0);
    waitpid(pid2, nullptr, 0);

    return 0;
}

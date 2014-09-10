program main

    implicit none

    integer, parameter :: n = 5
    integer x(n), i

    do i = 1, n
        x(i) = i
    end do

    print *, "[Notice]: Call foo_init."
    call foo_init()
    print *, "[Notice]: Call foo_set_data."
    call foo_set_data(n, x)
    print *, "[Notice]: Call foo_print_data."
    call foo_print_data()

end program main

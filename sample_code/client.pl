#!/usr/bin/perl

use strict;
use Socket;

my $host = shift || 'localhost';
my $port = shift || 9999;
my $server = "localhost";

socket(SOCKET, PF_INET, SOCK_STREAM, (getprotobyname('tcp'))[2])
    or die "Can't create a socket $!\n";

connect(SOCKET, pack_sockaddr_in($port, inet_aton($server)))
    or die "Can't connect to port $port! \n";

print SOCKET "hello world";

close SOCKET or die"close:$!";

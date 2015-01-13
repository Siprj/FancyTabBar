#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T22:15:21
#
#-------------------------------------------------

TEMPLATE = subdirs

# Needed to ensure that things are built right, which you have to do yourself :(
CONFIG += ordered

# All the projects in your application are sub-projects of your solution
SUBDIRS = FancyTabBar \
    example

# Use .depends to specify that a project depends on another.
example.depends = FancyTabBar

example.target = build

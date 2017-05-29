@extends('layouts.app')

@section('title')
    Welcome
@endsection

@section('content')


    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading">
                        MVO Tool Application
                    </div>

                    <div class="panel-body">
                        <p>Welcome to the app press the register button</p>
                        <a href="/register" class="btn btn-success">Create an Account</a>
<!--
                        <form action="resultTest.php">
                            <button type="submit" value="Open Script">
                                Run Script
                            </button>
                        </form>
                        <form action="clearTest.php">
                            <button type="submit" value="Open Script">
                                Clear Text
                            </button>
                        </form>
                        <p>
                            <?php
                            $myfilename = "output.txt";
                            if (file_exists($myfilename)) {
                                echo file_get_contents($myfilename);
                            }
                            ?>
                        </p>
                        -->
                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection

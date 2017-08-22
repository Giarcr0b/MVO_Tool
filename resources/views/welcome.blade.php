@extends('layouts.app')

@section('title')
    Welcome
@endsection

@section('content')


    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading panel-title">
                        MVO Tool Application
                    </div>

                    <div class="panel-body">
                        <h5>Welcome to the Mean Variance Optimisation application, to begin using the application please
                            please login or create an account.</h5>
                    </div>
                    <div class="panel-body">
                        <a href="/register" class="btn btn-success">Create an Account</a>
                        <a href="/login" class="btn btn-primary pull-right">Login</a>
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
